#include <windows.h>

// h... handle
// i... int
// sz.. string terminated with zero ('\0')

/* handle hInstance - repräsentiert die Daten die Windows intern über das Programm speichert
* (z.B. Speicherort der .EXE-Datei)
*
* handle hPrevInstance - Überbleibsel aus 16bit Zeiten (Programmkopiezähler)
*
* szCmdLine - Kommandozeilenparameter (ähnlich wie argv[1] ..argv[n]
* Wird in Vernknüpfungen verwendet
*
* iCmdShow - Legt fest wie Fenster startet (Maximiert, Minimiert usw.)
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    /* Param 1: handle eines Fenster (das lahmgelegt wird, solange msbox geöffnet ist)
     * Param 4:
     * Gruppe 1 (Buttons)
     * MB_OK                    0x00000000L     // OK
     * MB_OKCANCEL              0x00000001L     // Ok Abbrechen
     * MB_ABORTRETRYIGNORE      0x00000002L     // Abbrechen Widerholen Ignorieren
     * MB_YESNOCANCEL           0x00000003L     // Ja Nein Abbrechen
     * MB_YESNO                 0x00000004L     // Ja Nein
     * MB_RETRYCANCEL           0x00000005L     // Wiederholen Abbrechen
     *
     * Gruppe 2 (Fokus)
     * MB_DEFBUTTON1            0x00000000L
     * MB_DEFBUTTON2            0x00000100L
     * MB_DEFBUTTON3            0x00000200L
     * MB_DEFBUTTON4            0x00000300L
     *
     * Gruppe 3 (Symbol)
     * MB_ICONHAND              0x00000010L     // Stopsymbol
     * MB_ICONQUESTION          0x00000020L     // Fragezeichen
     * MB_ICONEXCLAMATION       0x00000030L     // Ausrufezeichen
     * MB_ICONASTERISK          0x00000040L     // Sternchen
     *
     * MB_HELP                  0x00004000L     // Hilfeschaltfläche
     *
     * Werte abrufen:
     * IDOK, IDCANCEL, IDYES, IDNO, IDABORT, IDRETRY, IDIGNORE, IDHELP
     */
    int result = MessageBox(NULL, TEXT("Hello Welt"), TEXT("HelloMsg"),MB_OKCANCEL | MB_DEFBUTTON3 | MB_ICONHAND);

    if(IDOK == result)
    {
        MessageBox(NULL, TEXT("Alles ok!") ,TEXT("ergebnis"), 0);
    }
    else if (IDCANCEL == result) {
        MessageBox(NULL, TEXT("abgebrochen!") ,TEXT("ergebnis"), 0);
    }//...

    // Speicherort der .EXE-Datei
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    MessageBox(NULL, buffer, TEXT("HelloMsg"),0x00004242);

   // MessageBox(NULL, szCmdLine, TEXT("HelloMsg"),0);

    return 0;
}

/* Compilieren über Dos:
 * VS -> Extras - Optionen - Registerkarte 'Erstellen' - Kontrollkästchen 'Makefile beim Speichern der Projektdatei exportierne'
 *
 * VCVARS32.BAT 1x ausführen (Umgebungsvariable gesetzt)
 *
 * CMD -> Projektverzeichnis
 * $ NMAKE /f MsgBox.mak CFG="MsgBox - Win32 Debug"
 * $ NMAKE /f MsgBox.mak CFG="MsgBox - Win32 Relaese"
 *
*/
