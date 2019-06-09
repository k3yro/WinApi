#include <stdio.h>
#include <string.h>
#include <wchar.h>

void testChar(void);
void testWChar(void);

int main()
{
    printf("Char\n====\n");
    testChar();
    printf("\nWChar\n=====\n");
    testWChar();

    printf("\nStringkonstanten\n================\n");
    printf("\"Hello!\"  (char) : %i\n", sizeof("Hello!"));
    printf("L\"Hello!\" (wchar): %i\n", sizeof(L"Hello!"));

    printf("\nBibliotheksfunktionen\n=====================\n");

    char *pChar = "Hello!";         // 0x48   0x65   0x6C   0x6C   0x6F   0x21
    // Aus Hello! wird 48 65 6C 6C 6F 21
    printf("Laenge pChar: %i\n", strlen(pChar)/*6*/);

    wchar_t *pWChar = L"Hello!";    // 0x0048 0x0065 0x006C 0x006C 0x006F 0x0021
    // Aus Hello! wird 48 00 65 00 6C 00 6C 00 6F 00 21 00
    printf("Laenge pWChar: %i (falsch)\n", strlen(pWChar)/*1*/); // erste 00 (0x00 == NUL) nach 48 terminiert den String (sz)

    //Loesung für wchar:
    printf("Laenge pWChar: %i (richtig)\n", wcslen(pWChar)/*1*/);

    //wprintf(L"16bit\n");




    return 0;
}

void testChar()
{
    char c = 'A'; // 0x41 (Ansii)
    printf("c = %i Byte\t// einzelnes Zeichen\n", sizeof(c));     // Ausgabe: c = 1 Byte

    char *p; // 4 Byte großer Zeiger

    p = "Hello!"; // Mit NUL (Schlusszeichen) sind 7 Bytes im statischen Bereich des Programms belegt.
    printf("p = %i Byte\t// Zeigergroesse\n", sizeof(p));         // Ausgabe: p = 4 Byte

    char a[10];
    printf("a = %i Byte\t// 10er Array\n", sizeof(a));            // Ausgabe: a = 10 Byte

    char b[] = "Hello!";
    printf("b = %i Byte\t// 7er Array\n", sizeof(b));             // Ausgabe: b = 7 Byte

    //In Funktion (lokal) mit String Konstante:
    static char d[] = "Hello!";
}

void testWChar()
{
    wchar_t c = 'A'; // 0x0041 (Unicode)
    printf("c = %i Byte\t// einzelnes Zeichen\n", sizeof(c));   // Ausgabe: c = 2 Byte

    wchar_t *p; // 4 Byte großer Zeiger

    // L für breite Zeichencodes (2 Byte pro Zeichen)
    p = L"Hello!";
    printf("p = %i Byte\t// Zeigergroesse\n", sizeof(p));       // Ausgabe: p = 4 Byte

    wchar_t a[10];
    printf("a = %i Byte\t// 10er Array\n", sizeof(a));          // Ausgabe: a = 20 Byte

    wchar_t b[] = L"Hello!";
    printf("b = %i Byte\t// 7er Array\n", sizeof(b));           // Ausgabe: b = 14 Byte

    //In Funktion mit String Konstante:
    static wchar_t d[] = L"Hello!";
}
