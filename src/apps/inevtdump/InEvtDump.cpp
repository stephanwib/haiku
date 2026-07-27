```cpp
/*
 * InputMonitor.cpp
 *
 * Small Haiku input event monitor.
 *
 * Purpose:
 *   - Display mouse movement
 *   - Display mouse button events
 *   - Display click counts
 *   - Display mouse wheel events
 *   - Display keyboard events
 *   - Display modifier changes
 *   - Print complete BMessages using PrintToStream()
 *
 * This is particularly useful for comparing:
 *
 *   Native Haiku app_server
 *          vs.
 *   Cosmoe/NetBSD + SDL app_server backend
 *
 * For the complete BMessages, it is best to run the application
 * from a terminal.
 */

#include <Application.h>
#include <Window.h>
#include <View.h>
#include <TextView.h>
#include <ScrollView.h>
#include <MessageFilter.h>
#include <String.h>

#include <stdio.h>


static const uint32 kClearLog = 'clrL';


/*
 * Convert a uint32/what value into a readable representation.
 *
 * Example:
 *
 *     B_MOUSE_DOWN
 *         -> 'mdwn' / 0x...
 *
 * Many Haiku messages use FourCC-style values.
 */
static BString
WhatToString(uint32 what)
{
	char fourcc[5];

	fourcc[0] = (char)((what >> 24) & 0xff);
	fourcc[1] = (char)((what >> 16) & 0xff);
	fourcc[2] = (char)((what >> 8) & 0xff);
	fourcc[3] = (char)(what & 0xff);
	fourcc[4] = '\0';

	bool printable = true;

	for (int i = 0; i < 4; i++) {
		unsigned char c = fourcc[i];

		if (c < 32 || c > 126) {
			printable = false;
			break;
		}
	}

	BString result;

	if (printable)
		result.SetToFormat(
			"'%s' (0x%08lx)",
			fourcc,
			(unsigned long)what);
	else
		result.SetToFormat(
			"0x%08lx",
			(unsigned long)what);

	return result;
}


/*
 * Convert the main Haiku mouse button flags into a readable list.
 */
static BString
ButtonsToString(int32 buttons)
{
	BString result;

	if (buttons == 0)
		return "none";

	if (buttons & B_PRIMARY_MOUSE_BUTTON)
		result << "PRIMARY ";

	if (buttons & B_SECONDARY_MOUSE_BUTTON)
		result << "SECONDARY ";

	if (buttons & B_TERTIARY_MOUSE_BUTTON)
		result << "TERTIARY ";

	return result;
}


/*
 * Convert Haiku modifier flags into a readable representation.
 *
 * The numeric representation is intentionally included as well.
 * For our port, the exact bit values are particularly interesting.
 */
static BString
ModifiersToString(int32 modifiers)
{
	BString result;

	result.SetToFormat("0x%08lx [",
		(unsigned long)(uint32)modifiers);

	if (modifiers & B_SHIFT_KEY)
		result << "SHIFT ";

	if (modifiers & B_CONTROL_KEY)
		result << "CONTROL ";

	if (modifiers & B_COMMAND_KEY)
		result << "COMMAND ";

	if (modifiers & B_OPTION_KEY)
		result << "OPTION ";

	if (modifiers & B_MENU_KEY)
		result << "MENU ";

	if (modifiers & B_CAPS_LOCK)
		result << "CAPS_LOCK ";

	if (modifiers & B_SCROLL_LOCK)
		result << "SCROLL_LOCK ";

	if (modifiers & B_NUM_LOCK)
		result << "NUM_LOCK ";

	if (modifiers & B_LEFT_SHIFT_KEY)
		result << "LEFT_SHIFT ";

	if (modifiers & B_RIGHT_SHIFT_KEY)
		result << "RIGHT_SHIFT ";

	if (modifiers & B_LEFT_CONTROL_KEY)
		result << "LEFT_CONTROL ";

	if (modifiers & B_RIGHT_CONTROL_KEY)
		result << "RIGHT_CONTROL ";

	if (modifiers & B_LEFT_COMMAND_KEY)
		result << "LEFT_COMMAND ";

	if (modifiers & B_RIGHT_COMMAND_KEY)
		result << "RIGHT_COMMAND ";

	if (modifiers & B_LEFT_OPTION_KEY)
		result << "LEFT_OPTION ";

	if (modifiers & B_RIGHT_OPTION_KEY)
		result << "RIGHT_OPTION ";

	result << "]";

	return result;
}


/*
 * Display the "bytes" BMessage field.
 *
 * UTF-8 may contain multiple bytes. Therefore we deliberately
 * display both the actual string and the hexadecimal byte values.
 */
static BString
BytesToHex(const char* bytes, int32 length)
{
	BString result;

	for (int32 i = 0; i < length; i++) {
		if (i != 0)
			result << " ";

		result << BString().SetToFormat(
			"%02x",
			(unsigned char)bytes[i]).String();
	}

	return result;
}


/*
 * Filter for all messages received by the window.
 *
 * BMessageFilter is particularly useful for this test:
 *
 *     app_server
 *          |
 *          v
 *     BMessageFilter
 *          |
 *          v
 *     normal Haiku event processing
 *
 * We do not modify the messages. We always return
 * B_DISPATCH_MESSAGE so normal processing continues.
 */
class RawEventFilter : public BMessageFilter {
public:
	RawEventFilter(BTextView* output)
		:
		BMessageFilter(),
		fOutput(output)
	{
	}


	virtual filter_result Filter(
		BMessage* message,
		BHandler** target)
	{
		if (message == NULL)
			return B_DISPATCH_MESSAGE;

		/*
		 * This output is particularly important for comparison.
		 *
		 * It contains the complete BMessage representation generated
		 * by Haiku.
		 *
		 * Therefore it is best to run the application from a terminal.
		 */
		printf("\n============================================================\n");

		BString what = WhatToString(message->what);

		printf("RAW BMessage: %s\n", what.String());
		message->PrintToStream();

		printf("============================================================\n");
		fflush(stdout);


		/*
		 * The UI only displays input-related messages in a
		 * human-readable form.
		 *
		 * All other messages are still printed completely above.
		 */
		switch (message->what) {
			case B_MOUSE_MOVED:
				ShowMouseMoved(message);
				break;

			case B_MOUSE_DOWN:
				ShowMouseButton(message, "B_MOUSE_DOWN");
				break;

			case B_MOUSE_UP:
				ShowMouseButton(message, "B_MOUSE_UP");
				break;

			case B_MOUSE_WHEEL_CHANGED:
				ShowMouseWheel(message);
				break;

			case B_KEY_DOWN:
				ShowKey(message, "B_KEY_DOWN");
				break;

			case B_KEY_UP:
				ShowKey(message, "B_KEY_UP");
				break;

			case B_UNMAPPED_KEY_DOWN:
				ShowKey(message, "B_UNMAPPED_KEY_DOWN");
				break;

			case B_UNMAPPED_KEY_UP:
				ShowKey(message, "B_UNMAPPED_KEY_UP");
				break;

			case B_MODIFIERS_CHANGED:
				ShowModifiers(message);
				break;

			default:
				break;
		}

		return B_DISPATCH_MESSAGE;
	}


private:

	void AddLine(const char* text)
	{
		if (fOutput == NULL)
			return;

		fOutput->Insert(text);
		fOutput->Insert("\n");

		/*
		 * Always scroll to the end of the log.
		 */
		fOutput->ScrollToOffset(
			fOutput->TextLength());
	}


	void ShowMouseMoved(BMessage* message)
	{
		BPoint where;
		int32 buttons = 0;
		int64 when = 0;

		message->FindPoint("where", &where);
		message->FindInt32("buttons", &buttons);
		message->FindInt64("when", &when);

		BString line;

		line.SetToFormat(
			"[MOUSE MOVED] "
			"when=%lld "
			"where=(%.1f, %.1f) "
			"buttons=0x%08lx [%s]",
			(long long)when,
			where.x,
			where.y,
			(unsigned long)(uint32)buttons,
			ButtonsToString(buttons).String());

		AddLine(line.String());
	}


	void ShowMouseButton(
		BMessage* message,
		const char* name)
	{
		BPoint where;
		int32 buttons = 0;
		int32 modifiers = 0;
		int32 clicks = 0;
		int64 when = 0;

		message->FindPoint("where", &where);
		message->FindInt32("buttons", &buttons);
		message->FindInt32("modifiers", &modifiers);
		message->FindInt32("clicks", &clicks);
		message->FindInt64("when", &when);

		BString line;

		line.SetToFormat(
			"[%s] "
			"when=%lld "
			"where=(%.1f, %.1f) "
			"buttons=0x%08lx [%s] "
			"modifiers=%s "
			"clicks=%ld",
			name,
			(long long)when,
			where.x,
			where.y,
			(unsigned long)(uint32)buttons,
			ButtonsToString(buttons).String(),
			ModifiersToString(modifiers).String(),
			(long)clicks);

		AddLine(line.String());
	}


	void ShowMouseWheel(BMessage* message)
	{
		float dx = 0.0f;
		float dy = 0.0f;
		int64 when = 0;

		message->FindFloat(
			"be:wheel_delta_x", &dx);

		message->FindFloat(
			"be:wheel_delta_y", &dy);

		message->FindInt64(
			"when", &when);

		BString line;

		line.SetToFormat(
			"[MOUSE WHEEL] "
			"when=%lld "
			"delta=(%.3f, %.3f)",
			(long long)when,
			dx,
			dy);

		AddLine(line.String());
	}


	void ShowModifiers(BMessage* message)
	{
		int32 modifiers = 0;
		int32 oldModifiers = 0;
		int64 when = 0;

		message->FindInt32(
			"modifiers", &modifiers);

		message->FindInt32(
			"be:old_modifiers",
			&oldModifiers);

		message->FindInt64(
			"when", &when);

		BString line;

		line.SetToFormat(
			"[MODIFIERS CHANGED] "
			"when=%lld "
			"old=%s "
			"new=%s",
			(long long)when,
			ModifiersToString(oldModifiers).String(),
			ModifiersToString(modifiers).String());

		AddLine(line.String());
	}


	void ShowKey(
		BMessage* message,
		const char* name)
	{
		int32 key = 0;
		int32 modifiers = 0;
		int32 repeat = -1;
		int32 rawChar = -1;
		int64 when = 0;

		int8 byte = 0;

		const char* bytes = NULL;

		message->FindInt32("key", &key);
		message->FindInt32("modifiers", &modifiers);
		message->FindInt64("when", &when);

		/*
		 * be:key_repeat is normally absent for the initial
		 * B_KEY_DOWN event.
		 */
		message->FindInt32(
			"be:key_repeat",
			&repeat);

		message->FindInt32(
			"raw_char",
			&rawChar);

		message->FindInt8(
			"byte",
			&byte);

		message->FindString(
			"bytes",
			&bytes);

		BString line;

		line.SetToFormat(
			"[%s] "
			"when=%lld "
			"key=0x%08lx (%ld) "
			"byte=0x%02x "
			"modifiers=%s",
			name,
			(long long)when,
			(unsigned long)(uint32)key,
			(long)key,
			(unsigned char)byte,
			ModifiersToString(modifiers).String());

		AddLine(line.String());


		if (bytes != NULL) {
			int32 length = (int32)strlen(bytes);

			BString textLine;

			textLine.SetToFormat(
				"    bytes=\"%s\"  hex=[%s]",
				bytes,
				BytesToHex(bytes, length).String());

			AddLine(textLine.String());
		}


		if (repeat >= 0) {
			BString repeatLine;

			repeatLine.SetToFormat(
				"    be:key_repeat=%ld",
				(long)repeat);

			AddLine(repeatLine.String());
		}


		if (rawChar >= 0) {
			BString rawLine;

			rawLine.SetToFormat(
				"    raw_char=0x%08lx (%ld)",
				(unsigned long)(uint32)rawChar,
				(long)rawChar);

			AddLine(rawLine.String());
		}
	}


	BTextView* fOutput;
};


/*
 * Main application window.
 */
class InputWindow : public BWindow {
public:
	InputWindow()
		:
		BWindow(
			BRect(100, 100, 1000, 700),
			"Haiku Input Monitor",
			B_TITLED_WINDOW,
			B_QUIT_ON_WINDOW_CLOSE),
		fOutput(NULL),
		fFilter(NULL)
	{
		/*
		 * TextView used as the event log.
		 */
		fOutput = new BTextView(
			Bounds().InsetByCopy(10, 10),
			"output",
			BRect(0, 0, 0, 0),
			B_FOLLOW_ALL,
			B_WILL_DRAW | B_NAVIGABLE);

		fOutput->MakeEditable(false);
		fOutput->SetWordWrap(false);

		BScrollView* scrollView = new BScrollView(
			"scroll",
			fOutput,
			B_FOLLOW_ALL,
			0,
			false,
			true);

		AddChild(scrollView);


		/*
		 * Install the filter as a common filter of the window.
		 *
		 * This allows it to observe all messages received by
		 * this BWindow.
		 */
		fFilter = new RawEventFilter(fOutput);
		AddCommonFilter(fFilter);


		/*
		 * Initial text.
		 */
		fOutput->Insert(
			"Haiku Input Monitor\n"
			"===================\n\n"
			"Move the mouse, press keys, modifiers, mouse buttons, "
			"and use the mouse wheel.\n"
			"Complete BMessages are also printed to the terminal.\n\n");
	}


	virtual bool QuitRequested()
	{
		be_app->PostMessage(B_QUIT_REQUESTED);
		return true;
	}


private:
	BTextView* fOutput;

	/*
	 * BWindow owns and manages the filter.
	 *
	 * No delete is necessary here.
	 */
	RawEventFilter* fFilter;
};


/*
 * Application class.
 */
class InputMonitorApp : public BApplication {
public:
	InputMonitorApp()
		:
		BApplication("application/x-vnd.example-InputMonitor")
	{
	}


	virtual void ReadyToRun()
	{
		InputWindow* window = new InputWindow();
		window->Show();
	}
};


/*
 * Program entry point.
 */
int
main()
{
	InputMonitorApp app;
	app.Run();

	return 0;
}
```
