#include <windows.h>
#include <stdio.h>

// Function to simulate a single key press
void PressKey(WORD vKey) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    // Press the key
    input.ki.wVk = vKey;
    input.ki.dwFlags = 0; 
    SendInput(1, &input, sizeof(INPUT));

    // Release the key
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

// Function to execute the "HESOYAM" sequence
void TriggerHesoyam() {
    printf("Triggering Macro...\n");
    WORD sequence[] = { 'H', 'E', 'S', 'O', 'Y', 'A', 'M' };
    for (int i = 0; i < 7; i++) {
        PressKey(sequence[i]);
        Sleep(50); // Small delay to mimic human typing and avoid input drops
    }
}

int main() {
    printf("Universal Macro Engine Active. Press F8 to trigger.\n");

    while (1) {
        // Listen for F8 key globally
        if (GetAsyncKeyState(VK_F8) & 0x8000) {
            TriggerHesoyam();
            Sleep(500); // Debounce to prevent multiple triggers
        }
        Sleep(10); // Reduce CPU usage
    }
    return 0;
}