#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <wchar.h>

typedef struct {
    char *sym;
    struct {
        char *sym;
        char *name;
    } html;
    char *desc;
} Char;

static Char ascii_table[] = {
    // control chars
    {"NUL", {"&#00;", ""}, "Null character"},
    {"SOH", {"&#01;", ""}, "Start of Heading"},
    {"STX", {"&#02;", ""}, "Start of Text"},
    {"ETX", {"&#03;", ""}, "End of Text"},
    {"EOT", {"&#04;", ""}, "End of Transmission"},
    {"ENQ", {"&#05;", ""}, "Enquiry"},
    {"ACK", {"&#06;", ""}, "Acknowledge"},
    {"BEL", {"&#07;", ""}, "Bell, Alert"},
    {"BS", {"&#08;", ""}, "Backspace"},
    {"HT", {"&#09;", ""}, "Horizontal Tab"},
    {"LF", {"&#10;", ""}, "Line Feed"},
    {"VT", {"&#11;", ""}, "Vertical Tabulation"},
    {"FF", {"&#12;", ""}, "Form Feed"},
    {"CR", {"&#13;", ""}, "Carriage Return"},
    {"SO", {"&#14;", ""}, "Shift Out"},
    {"SI", {"&#15;", ""}, "Shift In"},
    {"DLE", {"&#16;", ""}, "Data Link Escape"},
    {"DC1", {"&#17;", ""}, "Device Control One (XON)"},
    {"DC2", {"&#18;", ""}, "Device Control Two"},
    {"DC3", {"&#19;", ""}, "Device Control Three (XOFF)"},
    {"DC4", {"&#20;", ""}, "Device Control Four"},
    {"NAK", {"&#21;", ""}, "Negative Acknowledge"},
    {"SYN", {"&#22;", ""}, "Synchronous Idle"},
    {"ETB", {"&#23;", ""}, "End of Transmission Block"},
    {"CAN", {"&#24;", ""}, "Cancel"},
    {"EM", {"&#25;", ""}, "End of medium"},
    {"SUB", {"&#26;", ""}, "Substitute"},
    {"ESC", {"&#27;", ""}, "Escape"},
    {"FS", {"&#28;", ""}, "File Separator"},
    {"GS", {"&#29;", ""}, "Group Separator"},
    {"RS", {"&#30;", ""}, "Record Separator"},
    {"US", {"&#31;", ""}, "Unit Separator"},

    // printable chars
    {"SP", {"&#32;", ""}, "Space"},
    {"!", {"&#33;", "&excl;"}, "Exclamation mark"},
    {"\"", {"&#34;", "&quot;"}, "Double quotes (or speech marks)"},
    {"#", {"&#35;", "&num;"}, "Number sign"},
    {"$", {"&#36;", "&dollar;"}, "Dollar"},
    {"%", {"&#37;", "&percnt;"}, "Per cent sign"},
    {"&", {"&#38;", "&amp;"}, "Ampersand"},
    {"'", {"&#39;", "&apos;"}, "Single quote"},
    {"(", {"&#40;", "&lparen;"}, "Open parenthesis (or open bracket)"},
    {")", {"&#41;", "&rparen;"}, "Close parenthesis (or close bracket)"},
    {"*", {"&#42;", "&ast;"}, "Asterisk"},
    {"+", {"&#43;", "&plus;"}, "Plus"},
    {",", {"&#44;", "&comma;"}, "Comma"},
    {"-", {"&#45;", ""}, "Hyphen-minus"},
    {".", {"&#46;", "&period;"}, "Period, dot or full stop"},
    {"/", {"&#47;", "&sol;"}, "Slash or divide"},
    {"0", {"&#48;", ""}, "Zero"},
    {"1", {"&#49;", ""}, "One"},
    {"2", {"&#50;", ""}, "Two"},
    {"3", {"&#51;", ""}, "Three"},
    {"4", {"&#52;", ""}, "Four"},
    {"5", {"&#53;", ""}, "Five"},
    {"6", {"&#54;", ""}, "Six"},
    {"7", {"&#55;", ""}, "Seven"},
    {"8", {"&#56;", ""}, "Eight"},
    {"9", {"&#57;", ""}, "Nine"},
    {":", {"&#58;", "&colon;"}, "Colon"},
    {";", {"&#59;", "&semi;"}, "Semicolon"},
    {"<", {"&#60;", "&lt;"}, "Less than (or open angled bracket)"},
    {"=", {"&#61;", "&equals;"}, "Equals"},
    {">", {"&#62;", "&gt;"}, "Greater than (or close angled bracket)"},
    {"?", {"&#63;", "&quest;"}, "Question mark"},
    {"@", {"&#64;", "&commat;"}, "At sign"},
    {"A", {"&#65;", ""}, "Uppercase A"},
    {"B", {"&#66;", ""}, "Uppercase B"},
    {"C", {"&#67;", ""}, "Uppercase C"},
    {"D", {"&#68;", ""}, "Uppercase D"},
    {"E", {"&#69;", ""}, "Uppercase E"},
    {"F", {"&#70;", ""}, "Uppercase F"},
    {"G", {"&#71;", ""}, "Uppercase G"},
    {"H", {"&#72;", ""}, "Uppercase H"},
    {"I", {"&#73;", ""}, "Uppercase I"},
    {"J", {"&#74;", ""}, "Uppercase J"},
    {"K", {"&#75;", ""}, "Uppercase K"},
    {"L", {"&#76;", ""}, "Uppercase L"},
    {"M", {"&#77;", ""}, "Uppercase M"},
    {"N", {"&#78;", ""}, "Uppercase N"},
    {"O", {"&#79;", ""}, "Uppercase O"},
    {"P", {"&#80;", ""}, "Uppercase P"},
    {"Q", {"&#81;", ""}, "Uppercase Q"},
    {"R", {"&#82;", ""}, "Uppercase R"},
    {"S", {"&#83;", ""}, "Uppercase S"},
    {"T", {"&#84;", ""}, "Uppercase T"},
    {"U", {"&#85;", ""}, "Uppercase U"},
    {"V", {"&#86;", ""}, "Uppercase V"},
    {"W", {"&#87;", ""}, "Uppercase W"},
    {"X", {"&#88;", ""}, "Uppercase X"},
    {"Y", {"&#89;", ""}, "Uppercase Y"},
    {"Z", {"&#90;", ""}, "Uppercase Z"},
    {"[", {"&#91;", "&lsqb;"}, "Opening bracket"},
    {"\\", {"&#92;", "&bsol;"}, "Backslash"},
    {"]", {"&#93;", "&rsqb;"}, "Closing bracket"},
    {"^", {"&#94;", "&Hat;"}, "Caret - circumflex"},
    {"_", {"&#95;", "&lowbar;"}, "Underscore"},
    {"`", {"&#96;", "&grave;"}, "Grave accent"},
    {"a", {"&#97;", ""}, "Lowercase a"},
    {"b", {"&#98;", ""}, "Lowercase b"},
    {"c", {"&#99;", ""}, "Lowercase c"},
    {"d", {"&#100;", ""}, "Lowercase d"},
    {"e", {"&#101;", ""}, "Lowercase e"},
    {"f", {"&#102;", ""}, "Lowercase f"},
    {"g", {"&#103;", ""}, "Lowercase g"},
    {"h", {"&#104;", ""}, "Lowercase h"},
    {"i", {"&#105;", ""}, "Lowercase i"},
    {"j", {"&#106;", ""}, "Lowercase j"},
    {"k", {"&#107;", ""}, "Lowercase k"},
    {"l", {"&#108;", ""}, "Lowercase l"},
    {"m", {"&#109;", ""}, "Lowercase m"},
    {"n", {"&#110;", ""}, "Lowercase n"},
    {"o", {"&#111;", ""}, "Lowercase o"},
    {"p", {"&#112;", ""}, "Lowercase p"},
    {"q", {"&#113;", ""}, "Lowercase q"},
    {"r", {"&#114;", ""}, "Lowercase r"},
    {"s", {"&#115;", ""}, "Lowercase s"},
    {"t", {"&#116;", ""}, "Lowercase t"},
    {"u", {"&#117;", ""}, "Lowercase u"},
    {"v", {"&#118;", ""}, "Lowercase v"},
    {"w", {"&#119;", ""}, "Lowercase w"},
    {"x", {"&#120;", ""}, "Lowercase x"},
    {"y", {"&#121;", ""}, "Lowercase y"},
    {"z", {"&#122;", ""}, "Lowercase z"},
    {"{", {"&#123;", "&lcub;"}, "Opening brace"},
    {"|", {"&#124;", "&verbar;"}, "Vertical bar"},
    {"}", {"&#125;", "&rcub;"}, "Closing brace"},
    {"~", {"&#126;", "&tilde;"}, "Equivalency sign - tilde"},
    {"DEL", {"&#127;", ""}, "Delete"},

    // extended chars
    {"€", {"&#8364;", "&euro;"}, "Euro sign"},
    {"", {"", ""}, "Unused"},
    {"‚", {"&#130;", "&sbquo;"}, "Single low-9 quotation mark"},
    {"ƒ", {"&#131;", "&fnof;"}, "Latin small letter f with hook"},
    {"„", {"&#132;", "&bdquo;"}, "Double low-9 quotation mark"},
    {"…", {"&#133;", "&hellip;"}, "Horizontal ellipsis"},
    {"†", {"&#134;", "&dagger;"}, "Dagger"},
    {"‡", {"&#135;", "&Dagger;"}, "Double dagger"},
    {"ˆ", {"&#136;", "&circ;"}, "Modifier letter circumflex accent"},
    {"‰", {"&#137;", "&permil;"}, "Per mille sign"},
    {"Š", {"&#138;", "&Scaron;"}, "Latin capital letter S with caron"},
    {"‹", {"&#139;", "&lsaquo;"}, "Single left-pointing angle quotation"},
    {"Œ", {"&#140;", "&OElig;"}, "Latin capital ligature OE"},
    {"", {"", ""}, "Unused"},
    {"Ž", {"&#142;", "&Zcaron;"}, "Latin capital letter Z with caron"},
    {"", {"", ""}, "Unused"},
    {"", {"", ""}, "Unused"},
    {"'", {"&#145;", "&lsquo;"}, "Left single quotation mark"},
    {"'", {"&#146;", "&rsquo;"}, "Right single quotation mark"},
    {"\"", {"&#147;", "&ldquo;"}, "Left double quotation mark"},
    {"\"", {"&#148;", "&rdquo;"}, "Right double quotation mark"},
    {"•", {"&#149;", "&bull;"}, "Bullet"},
    {"–", {"&#150;", "&ndash;"}, "En dash"},
    {"—", {"&#151;", "&mdash;"}, "Em dash"},
    {"˜", {"&#152;", "&tilde;"}, "Small tilde"},
    {"™", {"&#153;", "&trade;"}, "Trade mark sign"},
    {"š", {"&#154;", "&scaron;"}, "Latin small letter S with caron"},
    {"›", {"&#155;", "&rsaquo;"}, "Single right-pointing angle quotation mark"},
    {"œ", {"&#156;", "&oelig;"}, "Latin small ligature oe"},
    {"", {"", ""}, "Unused"},
    {"ž", {"&#158;", "&zcaron;"}, "Latin small letter z with caron"},
    {"Ÿ", {"&#159;", "&Yuml;"}, "Latin capital letter Y with diaeresis"},
    {"NBSP", {"&#160;", "&nbsp;"}, "Non-breaking space"},
    {"¡", {"&#161;", "&iexcl;"}, "Inverted exclamation mark"},
    {"¢", {"&#162;", "&cent;"}, "Cent sign"},
    {"£", {"&#163;", "&pound;"}, "Pound sign"},
    {"¤", {"&#164;", "&curren;"}, "Currency sign"},
    {"¥", {"&#165;", "&yen;"}, "Yen sign"},
    {"¦", {"&#166;", "&brvbar;"}, "Pipe, broken vertical bar"},
    {"§", {"&#167;", "&sect;"}, "Section sign"},
    {"¨", {"&#168;", "&uml;"}, "Spacing diaeresis - umlaut"},
    {"©", {"&#169;", "&copy;"}, "Copyright sign"},
    {"ª", {"&#170;", "&ordf;"}, "Feminine ordinal indicator"},
    {"«", {"&#171;", "&laquo;"}, "Left double angle quotes"},
    {"¬", {"&#172;", "&not;"}, "Negation"},
    {"SHY", {"&#173;", "&shy;"}, "Soft hyphen"},
    {"®", {"&#174;", "&reg;"}, "Registered trade mark sign"},
    {"¯", {"&#175;", "&macr;"}, "Spacing macron - overline"},
    {"°", {"&#176;", "&deg;"}, "Degree sign"},
    {"±", {"&#177;", "&plusmn;"}, "Plus-or-minus sign"},
    {"²", {"&#178;", "&sup2;"}, "Superscript two - squared"},
    {"³", {"&#179;", "&sup3;"}, "Superscript three - cubed"},
    {"´", {"&#180;", "&acute;"}, "Acute accent - spacing acute"},
    {"µ", {"&#181;", "&micro;"}, "Micro sign"},
    {"¶", {"&#182;", "&para;"}, "Pilcrow sign - paragraph sign"},
    {"·", {"&#183;", "&middot;"}, "Middle dot - Georgian comma"},
    {"¸", {"&#184;", "&cedil;"}, "Spacing cedilla"},
    {"¹", {"&#185;", "&sup1;"}, "Superscript one"},
    {"º", {"&#186;", "&ordm;"}, "Masculine ordinal indicator"},
    {"»", {"&#187;", "&raquo;"}, "Right double angle quotes"},
    {"¼", {"&#188;", "&frac14;"}, "Fraction one quarter"},
    {"½", {"&#189;", "&frac12;"}, "Fraction one half"},
    {"¾", {"&#190;", "&frac34;"}, "Fraction three quarters"},
    {"¿", {"&#191;", "&iquest;"}, "Inverted question mark"},
    {"À", {"&#192;", "&Agrave;"}, "Latin capital letter A with grave"},
    {"Á", {"&#193;", "&Aacute;"}, "Latin capital letter A with acute"},
    {"Â", {"&#194;", "&Acirc;"}, "Latin capital letter A with circumflex"},
    {"Ã", {"&#195;", "&Atilde;"}, "Latin capital letter A with tilde"},
    {"Ä", {"&#196;", "&Auml;"}, "Latin capital letter A with diaeresis"},
    {"Å", {"&#197;", "&Aring;"}, "Latin capital letter A with ring above"},
    {"Æ", {"&#198;", "&AElig;"}, "Latin capital letter AE"},
    {"Ç", {"&#199;", "&Ccedil;"}, "Latin capital letter C with cedilla"},
    {"È", {"&#200;", "&Egrave;"}, "Latin capital letter E with grave"},
    {"É", {"&#201;", "&Eacute;"}, "Latin capital letter E with acute"},
    {"Ê", {"&#202;", "&Ecirc;"}, "Latin capital letter E with circumflex"},
    {"Ë", {"&#203;", "&Euml;"}, "Latin capital letter E with diaeresis"},
    {"Ì", {"&#204;", "&Igrave;"}, "Latin capital letter I with grave"},
    {"Í", {"&#205;", "&Iacute;"}, "Latin capital letter I with acute"},
    {"Î", {"&#206;", "&Icirc;"}, "Latin capital letter I with circumflex"},
    {"Ï", {"&#207;", "&Iuml;"}, "Latin capital letter I with diaeresis"},
    {"Ð", {"&#208;", "&ETH;"}, "Latin capital letter ETH"},
    {"Ñ", {"&#209;", "&Ntilde;"}, "Latin capital letter N with tilde"},
    {"Ò", {"&#210;", "&Ograve;"}, "Latin capital letter O with grave"},
    {"Ó", {"&#211;", "&Oacute;"}, "Latin capital letter O with acute"},
    {"Ô", {"&#212;", "&Ocirc;"}, "Latin capital letter O with circumflex"},
    {"Õ", {"&#213;", "&Otilde;"}, "Latin capital letter O with tilde"},
    {"Ö", {"&#214;", "&Ouml;"}, "Latin capital letter O with diaeresis"},
    {"×", {"&#215;", "&times;"}, "Multiplication sign"},
    {"Ø", {"&#216;", "&Oslash;"}, "Latin capital letter O with slash"},
    {"Ù", {"&#217;", "&Ugrave;"}, "Latin capital letter U with grave"},
    {"Ú", {"&#218;", "&Uacute;"}, "Latin capital letter U with acute"},
    {"Û", {"&#219;", "&Ucirc;"}, "Latin capital letter U with circumflex"},
    {"Ü", {"&#220;", "&Uuml;"}, "Latin capital letter U with diaeresis"},
    {"Ý", {"&#221;", "&Yacute;"}, "Latin capital letter Y with acute"},
    {"Þ", {"&#222;", "&THORN;"}, "Latin capital letter THORN"},
    {"ß", {"&#223;", "&szlig;"}, "Latin small letter sharp s - ess-zed"},
    {"à", {"&#224;", "&agrave;"}, "Latin small letter a with grave"},
    {"á", {"&#225;", "&aacute;"}, "Latin small letter a with acute"},
    {"â", {"&#226;", "&acirc;"}, "Latin small letter a with circumflex"},
    {"ã", {"&#227;", "&atilde;"}, "Latin small letter a with tilde"},
    {"ä", {"&#228;", "&auml;"}, "Latin small letter a with diaeresis"},
    {"å", {"&#229;", "&aring;"}, "Latin small letter a with ring above"},
    {"æ", {"&#230;", "&aelig;"}, "Latin small letter ae"},
    {"ç", {"&#231;", "&ccedil;"}, "Latin small letter c with cedilla"},
    {"è", {"&#232;", "&egrave;"}, "Latin small letter e with grave"},
    {"é", {"&#233;", "&eacute;"}, "Latin small letter e with acute"},
    {"ê", {"&#234;", "&ecirc;"}, "Latin small letter e with circumflex"},
    {"ë", {"&#235;", "&euml;"}, "Latin small letter e with diaeresis"},
    {"ì", {"&#236;", "&igrave;"}, "Latin small letter i with grave"},
    {"í", {"&#237;", "&iacute;"}, "Latin small letter i with acute"},
    {"î", {"&#238;", "&icirc;"}, "Latin small letter i with circumflex"},
    {"ï", {"&#239;", "&iuml;"}, "Latin small letter i with diaeresis"},
    {"ð", {"&#240;", "&eth;"}, "Latin small letter eth"},
    {"ñ", {"&#241;", "&ntilde;"}, "Latin small letter n with tilde"},
    {"ò", {"&#242;", "&ograve;"}, "Latin small letter o with grave"},
    {"ó", {"&#243;", "&oacute;"}, "Latin small letter o with acute"},
    {"ô", {"&#244;", "&ocirc;"}, "Latin small letter o with circumflex"},
    {"õ", {"&#245;", "&otilde;"}, "Latin small letter o with tilde"},
    {"ö", {"&#246;", "&ouml;"}, "Latin small letter o with diaeresis"},
    {"÷", {"&#247;", "&divide;"}, "Division sign"},
    {"ø", {"&#248;", "&oslash;"}, "Latin small letter o with slash"},
    {"ù", {"&#249;", "&ugrave;"}, "Latin small letter u with grave"},
    {"ú", {"&#250;", "&uacute;"}, "Latin small letter u with acute"},
    {"û", {"&#251;", "&ucirc;"}, "Latin small letter u with circumflex"},
    {"ü", {"&#252;", "&uuml;"}, "Latin small letter u with diaeresis"},
    {"ý", {"&#253;", "&yacute;"}, "Latin small letter y with acute"},
    {"þ", {"&#254;", "&thorn;"}, "latin small letter thorn"},
    {"ÿ", {"&#255;", "&yuml;"}, "Latin small letter y with diaeresis"}
};

void usage()
{
    printf("ascii print ASCII table\n\n");
    printf("Usage:\n");
    printf("  ascii [OPTION]...\n\n");

    printf("\nOptions:\n");
    printf("  -h, --help               show this help, then exit\n");
    printf("  -c, --control            show control characters\n");
    printf("  -p, --printable          show printable characters\n");
    printf("  -e, --extended           show extended characters\n");
    printf("  -a, --all                show all characters\n");
}

struct options {
    bool control;
    bool printable;
    bool extended;
};

static void parse_options(int argc, char *argv[], struct options *opts) 
{
    int ch;
    FILE *fd;

    /* options descriptor */
    static struct option longopts[] = {
        { "help",        no_argument,       NULL, 'h' },
        { "control",     no_argument,       NULL, 'c' },
        { "printable",   no_argument,       NULL, 'p' },
        { "extended",    no_argument,       NULL, 'e' },
        { "all",         no_argument,       NULL, 'a' },
        { NULL,          0,                 NULL,  0  }
    };

    while ((ch = getopt_long(argc, argv, "hcpea", longopts, NULL)) != -1) {
        switch (ch) {
            case 'c':
                opts->control = true;
                break;
            case 'p':
                opts->printable = true;
                break;
            case 'e':
                opts->extended = true;
                break;
            case 'a':
                opts->control = true;
                opts->printable = true;
                opts->extended = true;
                break;
            case 'h':
                usage();
                exit(0);
                break;
            default:
                fprintf(stderr, "Try: ascii --help\n");
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;

    // default to printable if nothing is set
    if (!opts->control && !opts->printable && !opts->extended)
        opts->printable = true;
}

int main(int argc, char *argv[]) 
{
    struct options opts = {0};
    parse_options(argc, argv, &opts);

    printf("|%s|%s|%s|%-43s|\n", "  Dec  ", "  Hex   ", "  Sym  ", " Description");
    printf("+%s+%s+%s+%s+\n",    "-------", "--------", "-------", "-------------------------------------------");

    if (opts.control) {
        // Control Charaters
        for (unsigned char c = 0; c <= 31; c++) {
            printf("|  %3d  |  0x%02x  |   %-3s |  %-40s |\n", 
                    c,  // decimal
                    c,  // hex
                    ascii_table[c].sym,  // char
                    ascii_table[c].desc // description
            );
        }
    }

    if (opts.printable) {
        // Printable Charaters
        for (unsigned char c = 32; c <= 127; c++) {
            printf("|  %3d  |  0x%02x  |   %-3s |  %-40s |\n", 
                    c,  // decimal
                    c,  // hex
                    ascii_table[c].sym,  // char
                    ascii_table[c].desc // description
            );
        }
    }

    if (opts.extended) {
        // Extened Charaters
        for (unsigned char c = 128; c >= 128; c++) { // note the overflow
            printf("|  %3d  |  0x%02x  |   %-3s |  %-40s |\n", 
                    c,  // decimal
                    c,  // hex
                    ascii_table[c].sym,  // char
                    ascii_table[c].desc // description
            );
 
        }
    }
    printf("+%s+%s+%s+%s+\n",    "-------", "--------", "-------", "-------------------------------------------");

    return 0;
}
