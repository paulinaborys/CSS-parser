#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>

using namespace std;

int stringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

bool stringCompare(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str1[i] == str2[i]) {
        ++i;
    }
    return (str1[i] == str2[i]);
}

void stringCopy(char* destination, const char* source) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        ++i;
    }
    destination[i] = '\0';
}

const char* stringChr(const char* str, int c)
{
    while (*str != '\0')
    {
        if (*str == c)


        {
            return str;
        }
        str++;
    }

    return nullptr;
}


struct Attribute
{
    char* property;
    char* value;
    Attribute* next;
    Attribute* prev;
};

//lista dwukierunkowa
struct AttributeList {
    Attribute* head;
    Attribute* tail;
    int count;
    AttributeList();
    ~AttributeList();
    void push_attribute_front(const char* property, const char* value);
    void push_attribute_back(const char* property, const char* value);
    void print();
    void print_value(const char* property);
    void print_back();
    int count_attribute_of_property(const char* property);
    Attribute* get_attribute_of_property_front(const char* property);
    Attribute* get_attribute_of_property_back(const char* property);
    void remove_attribute_of_property(const char* property);
};

AttributeList::AttributeList() {
    head = NULL;
    tail = NULL;
    count = 0;
}

AttributeList::~AttributeList() {
    Attribute* temp;
    while (head) {
        temp = head->next;
        delete head;
        head = temp;
    }
    count = 0;
}

void AttributeList::push_attribute_front(const char* property, const char* value) {

    Attribute* temp = new Attribute;

    temp->property = new char(stringLength(property) + 1);
    stringCopy(temp->property, property);

    temp->value = new char(stringLength(value) + 1);
    stringCopy(temp->value, value);

    temp->prev = NULL;
    temp->next = head;
    if (head) {
        head->prev = temp;
    }
    head = temp;
    if (!tail) {
        tail = head;
    }
    count++;
}

void AttributeList::push_attribute_back(const char* property, const char* value) {
    Attribute* temp = new Attribute;
    
    temp->property = new char(stringLength(property) + 1);
    stringCopy(temp->property, property);

    // wskaznik na ostatni element listy
    Attribute* itrr = tail;
    bool isDuplicate = false;
    // przewijamy wskazniki na nastepne elementy
    while (itrr != NULL)
    {
        if (stringCompare(property, itrr->property) == 1)
        {
            //istnieje taki atrybut
            isDuplicate = true;
            itrr->value = new char(stringLength(value) + 1);
            stringCopy(itrr->value, value);
            break;
        }
        itrr = itrr->prev;
    }

    if (!isDuplicate) {
        temp->value = new char(stringLength(value) + 1);
        stringCopy(temp->value, value);

        if (tail) {
            tail->next = temp;
        }
        temp->next = NULL;
        temp->prev = tail;
        tail = temp;
        if (!head) {
            head = tail;
        }
        count++;
    }

}



void AttributeList::print() {
    // wskaznik na pierszy element listy
    Attribute* temp = head;

    // przewijamy wskazniki na nastepne elementy
    while (temp != NULL)
    {
        printf("property: %s value: %s\n", temp->property, temp->value);
        temp = temp->next;
    }
}

void AttributeList::print_value(const char* property) {
    // wskaznik na pierszy element listy
    Attribute* temp = head;
    // przewijamy wskazniki na nastepne elementy
    while (temp != NULL)
    {
        if (stringCompare(property, temp->property) == 1)
        {
            printf("%s\n", temp->value);
            return;
        }
        temp = temp->next;
    }

}

void AttributeList::print_back() {
    // wskaznik na pierszy element listy
    Attribute* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
        cout << "property: " << temp->property << " value: " << temp->value << endl;
        temp = temp->prev;
    }
}

int AttributeList::count_attribute_of_property(const char* property) {
    // wskaznik na pierszy element listy
    Attribute* temp = head;
    int attribute_counter = 0;
    // przewijamy wskazniki na nastepne elementy
    while (temp != NULL)
    {
        if (stringCompare(property, temp->property) == 1)
        {
            attribute_counter++;
        }
        temp = temp->next;
    }
    return attribute_counter;
}

Attribute* AttributeList::get_attribute_of_property_front(const char* property) {
    // wskaznik na pierszy element listy
    Attribute* temp = head;
    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
        if (stringCompare(property, temp->property) == 1)
        {
            return temp;
        }
        temp = temp->next;
    }
}

Attribute* AttributeList::get_attribute_of_property_back(const char* property) {
    // wskaznik na ostatni element listy
    Attribute* temp = tail;
    // przewijamy wskazniki na nastepne elementy
    while (temp != NULL)
    {
        if (stringCompare(property, temp->property) == 1)
        {
            return temp;
        }
        temp = temp->prev;
    }
}

void AttributeList::remove_attribute_of_property(const char* property) {
    Attribute* temp = get_attribute_of_property_back(property);

    if (temp->prev) {
        temp->prev->next = temp->next;
    }
    else {
        head = temp->next;
    }
    if (temp->next) {
        temp->next->prev = temp->prev;
    }
    else {
        tail = temp->prev;
    }
    count--;
}


struct Selector
{
    char* name;
    Selector* next;
};

struct SelectorList {
    Selector* head;
    int count;
    SelectorList();
    ~SelectorList();
    void add_selector(const char* name);
    void print();
    Selector* find_selector_of_index(int j);
    int count_selector_of_name(const char* name);
};

SelectorList::SelectorList() {
    head = NULL;
    count = 0;
}

SelectorList::~SelectorList() {
    Selector* temp = new Selector;
    while (head) {
        temp = head->next;
        delete head;
        head = temp;
    }
    count = 0;
}

void SelectorList::add_selector(const char* name) {
    Selector* new_selec = new Selector;    // tworzy nowy atrybut

    // wypełniamy danymi
    new_selec->name = new char(stringLength(name) + 1);
    stringCopy(new_selec->name, name);

    if (!head) // sprawdzamy czy to pierwszy element listy
    {
        // jeżeli tak to nowy element jest teraz początkiem listy
        head = new_selec;
        head->next = NULL;
    }
    else
    {
        // w przeciwnym wypadku wędrujemy na koniec listy
        Selector* temp = head;

        while (temp->next)
        {
            // znajdujemy wskaźnik na ostatni element
            temp = temp->next;
        }

        temp->next = new_selec;  // ostatni element wskazuje na nasz nowy
        new_selec->next = NULL;     // ostatni nie wskazuje na nic
    }
    count++;
}


void SelectorList::print() {
    // wskaznik na pierszy element listy
    Selector* temp = head;

    // przewijamy wskazniki na nastepne elementy
    while (temp != NULL)
    {
        printf("selector name: %s\n", temp->name);
        temp = temp->next;
    }
}

Selector* SelectorList::find_selector_of_index(int j) {

    Selector* temp = head;
    if (j > count) {
        return NULL;
    }
    for (int i = 0; i < j; i++) {
        if (temp != NULL) {
            temp = temp->next;
        }
        else {
            break;
        }
    }
    return temp;

}
int SelectorList::count_selector_of_name(const char* name) {
    // wskaznik na pierszy element listy
    Selector* temp = head;
    int selector_counter = 0;
    // przewijamy wskazniki na nastepne elementy
    while (temp != NULL)
    {
        if (stringCompare(name, temp->name) == 1)
        {
            selector_counter++;
        }
        temp = temp->next;
    }
    return selector_counter;
}

struct Block
{
    //lista jednokierunkowa
    SelectorList* selectors_list;
    //lista dwukierunkowa
    AttributeList* attributes_list;
    Block();
};

Block::Block() {
    selectors_list = new SelectorList();
    attributes_list = new AttributeList();
}

void parseCss(const char* text, Block* Blocks, int& block_counter, const int T) {
    printf("Parse CSS\n");
    const int bufferSize = 1000;
    char selector[bufferSize];
    char property[bufferSize];
    char value[bufferSize];

    int selectorIndex = 0;
    int propertyIndex = 0;
    int valueIndex = 0;

    bool readingSelector = false;
    bool readingProperty = false;
    bool readingValue = false;

    SelectorList* selectors = new SelectorList();
    AttributeList* attributes = new AttributeList();


    for (int i = 0; text[i] != '\0'; ++i) {
        char currentChar = text[i];
        if (currentChar == '{') {
            if (selectorIndex > 0) {
                selector[selectorIndex] = '\0';
                //printf("Selektor1: selector=%s\n", selector);
                Blocks[block_counter].selectors_list->add_selector(selector);
                selectorIndex = 0;
            }
            readingProperty = true;
            readingSelector = false;
            propertyIndex = 0;
        }
        else if (currentChar == ',' && readingSelector) {
            selector[selectorIndex] = '\0';
            //printf("Selektor2: selector=%s\n", selector);
            Blocks[block_counter].selectors_list->add_selector(selector);
            readingSelector = true;
            selectorIndex = 0;
        }
        else if (currentChar == ':') {
            readingValue = true;
            readingProperty = false;
            valueIndex = 0;
        }
        else if (currentChar == ';') {
            property[propertyIndex] = '\0';
            value[valueIndex] = '\0';
            //printf("Atrybut1: property=%s, value=%s\n", property, value);
            Blocks[block_counter].attributes_list->push_attribute_back(property, value);
            readingProperty = true;
            propertyIndex = 0;
            valueIndex = 0;
        }
        else if (currentChar == ',' && readingValue) {
            property[propertyIndex] = '\0';
            value[valueIndex] = '\0';
            //printf("Atrybut2: property=%s, value=%s\n", property, value);
            Blocks[block_counter].attributes_list->push_attribute_back(property, value);
            readingValue = true;
            valueIndex = 0;
        }
        else if (currentChar == '}') {
            property[propertyIndex] = '\0';
            value[valueIndex] = '\0';

            if (!stringCompare(property, "") && !stringCompare(value, "")) {
                Blocks[block_counter].attributes_list->push_attribute_back(property, value);
                propertyIndex = 0;
                valueIndex = 0;
            }

            property[propertyIndex] = '\0';
            value[valueIndex] = '\0';

            readingSelector = false;
            readingProperty = false;
            readingValue = false;

            printf("Block counter = %d\n", block_counter);
            Blocks[block_counter].selectors_list->print();
            Blocks[block_counter].attributes_list->print();
            if (block_counter < T - 1) block_counter++;
            else {
                block_counter = 0;
                Blocks[block_counter].selectors_list->~SelectorList();
                Blocks[block_counter].attributes_list->~AttributeList();
            }            
        }
        else {
            if (!readingSelector && !readingProperty && !readingValue && currentChar != ' ') {
                readingSelector = true;
            }
            if(currentChar == '\n' || currentChar == ' '){
                continue;
            }
            if (readingSelector) {
                selector[selectorIndex++] = currentChar;
            }
            else if (readingProperty) {
                    property[propertyIndex++] = currentChar;
            }
            else if (readingValue) {
                value[valueIndex++] = currentChar;
            }
        }
    }
}

int parseNumber(const char* start_command, const char* end_command) {
    int i = 0;
    for (const char* p = start_command; p < end_command; p++) {
        if (*p >= '0' && *p <= '9') {
            i = i * 10 + (*p - '0');
        }
        else {
            return -1;
        }

    }
    return i;
}

char* parseWord(const char* start_command, const char* end_command) {
    char* word = new char[end_command - start_command + 1];
    int j = 0;
    for (const char* p = start_command; p < end_command; p++) {
        word[j++] = *p;
    }
    return word;
}



void parseCommands(Block* Blocks, int& block_counter) {
    printf("Komendy:\n");

    int commandSize = 85;

    while (true) {
        char* command = new char[commandSize];
        scanf("%s", command);

        if (command[0] == '*' && command[1] == '*' && command[2] == '*' && command[3] == '*') return;
        if (command[0] == '?') {
            //wypisz liczbe blokow
            printf("? == %d\n", block_counter);
        }
        else {
            // Reszta komend
            const char* command_1 = stringChr(command, ',');            //adres pierwszego przecinka
            const char* command_2 = stringChr(command_1 + 1, ',');      //adres drugiego przecinka
            const char* command_3 = command + stringLength(command);    //adres końca komendy

            if (command[command_1 - command + 1] == 'S') {
                if (command[command_2 - command + 1] == '?') {
                    int i = 0;
                    char* word = new char[command_1 - command + 1];
                    int j = 0;
                    bool isWord = true;
                    bool isFirstCharacterDigit = true;

                    for (const char* p = command; p < command_1; p++) {
                        if (*p >= '0' && *p <= '9' && isFirstCharacterDigit) {
                            //liczba,S,?
                            i = i * 10 + (*p - '0');
                            isWord = false;
                            if (j == 0) {
                                isFirstCharacterDigit = true;
                            }
                        }
                        else {
                            // word,S,?
                            if (isFirstCharacterDigit) {
                                word[j++] = *p;
                                isFirstCharacterDigit = false;
                            }
                            else {
                                word[j++] = *p;
                            }
                        }
                    }
                    if (isWord && j > 0) {
                        // z,S,?
                        word[j] = '\0';
                        printf("Wywołano komendę 1 %s,S,? ==\n", word);
                        int selector_counter = 0;
                        for (int k = 0; k < block_counter; k++) {
                            selector_counter += Blocks[k].selectors_list->count_selector_of_name(word);
                        }
                        printf("%s,S,? == %d\n", word, selector_counter);
                    }
                    else {
                        // i,S,?
                        printf("Wywołano komendę 2 %d,S,? ==\n", i);
                        if (block_counter >= i) {
                            printf("%d,S,? == %d\n", i, Blocks[i - 1].selectors_list->count);
                        }
                    }
                    delete[] word;
                }
                else if (command[command_2 - command + 1] >= '0' && command[command_2 - command + 1] <= '9') {
                    // && command[0] >= '0' && command[0]<= '9'
                    // i,S,j
                    int i = parseNumber(command, command_1);
                    int j = parseNumber(command_2 + 1, command_3);
                    // sprawdz czy powinnow w word byc command_3 +1 czy command_3
                    if (i >= 0 && j >= 0) printf("Wywołano komendę 3 %d,S,%d ==\n", i, j);
                    if (block_counter >= i && i >= 0 && j >= 0) {
                        Selector* result = Blocks[i - 1].selectors_list->find_selector_of_index(j - 1);
                        if (result != NULL) {
                            printf("%d,S,%d == %s\n", i, j, result->name);
                        }
                    }
                }

            }
            else if (command[command_1 - command + 1] == 'A') {
                if (command[command_2 - command + 1] == '?') {
                    int i = 0;
                    char* word = new char[command_1 - command + 1];
                    int j = 0;
                    bool isWord = true;
                    bool isFirstCharacterDigit = true;

                    for (const char* p = command; p < command_1; p++) {
                        if (*p >= '0' && *p <= '9' && isFirstCharacterDigit) {
                            //liczba,A,?
                            i = i * 10 + (*p - '0');
                            isWord = false;
                            if (j == 0) {
                                isFirstCharacterDigit = true;
                            }
                        }
                        else {
                            // word,A,?
                            if (isFirstCharacterDigit) {
                                word[j++] = *p;
                                isFirstCharacterDigit = false;
                            }
                            else {
                                word[j++] = *p;
                            }
                        }
                    }
                    if (isWord && j > 0) {
                        word[j] = '\0';
                        printf("Wywołano komendę 4 %s,A,? ==\n", word);
                        // TODO perzeszukuj tylko wypelnione block_counter??T 
                        int attribute_counter = 0;
                        for (int i = 0; i < block_counter; i++) {
                            printf("atrybuty:\n");
                            Blocks[i].attributes_list->print();
                            //TODO usun spacje z poczatku property i value
                            attribute_counter += Blocks[i].attributes_list->count_attribute_of_property(word);
                        }
                        printf("%s,A,? == %d\n", word, attribute_counter);
                    }
                    else {
                        printf("Wywołano komendę 5 %d,A,? ==\n", i);
                        if (block_counter >= i) {
                            printf("%d,A,? == %d\n", i, Blocks[i - 1].attributes_list->count);
                        }
                    }
                    delete[] word;
                }
                else {
                    // i,A,n
                    int i = parseNumber(command, command_1);
                    char* word = parseWord(command_2 + 1, command_3 + 1);
                    if (i >= 0) printf("Wywołano komendę 6 %d,A,%s ==\n", i, word);
                    if (block_counter >= i && i >= 0) {
                        Blocks[i - 1].attributes_list->print();
                        // printf("%d,A,%s == %s\n", i, word, Blocks[i - 1].attributes_list->get_attribute_of_property_back(word)->value);
                        printf("%d,A,%s == ", i, word);
                        Blocks[i - 1].attributes_list->print_value(word);
                    }
                    delete[] word;
                }

            }
            else if (command[command_1 - command + 1] == 'E') {
                // z,E,n
                char* word1 = parseWord(command, command_1);
                char* word2 = parseWord(command_2 + 1, command_3 + 1);
                printf("Wywołano komendę 7 %s,E,%s ==\n", word1, word2);
                printf("%s,E,%s ==\n", word1, word2);
                for (int i = 0; i < block_counter; i++) {
                    //znajdz blok w ktorym jest taki selektor
                    if (Blocks[i].selectors_list->count_selector_of_name(word1) > 0) {
                        //znajdz od konca wartosc atrybutu o takiej nazwie
                        printf("%s,E,%s == %s\n", word1, word2, Blocks[i].attributes_list->get_attribute_of_property_back(word2)->value);
                    }
                }

                delete[] word1;
                delete[] word2;

            }
            else if (command[command_1 - command + 1] == 'D') {
                if (command[command_2 - command + 1] == '*') {
                    // i,D,*
                    int i = parseNumber(command, command_1);
                    if (block_counter >= i && i >= 0) {
                        printf("Wywołano komendę 8 %d,D,* ==\n", i);
                        Blocks[i - 1].attributes_list->~AttributeList();
                        Blocks[i - 1].selectors_list->~SelectorList();
                        printf("%d,D,* == %s\n", i, "deleted");
                    }

                }
                else {
                    // i,D,n
                    int i = parseNumber(command, command_1);
                    char* word = parseWord(command_2 + 1, command_3 + 1);
                    printf("Wywołano komendę 9 %d,D,%s ==\n", i, word);
                    // printf("%d,D,%s ==\n", i, word);
                    if (block_counter >= i && i >= 0) {
                        Blocks[i - 1].attributes_list->remove_attribute_of_property(word);
                        printf("%d,D,%s == %s\n", i, word, "deleted");
                    }
                    delete[] word;
                }
            }
        }
    }
}


int main() {

    const int T = 8;
    Block Blocks[T];
    int block_counter = 0;


    const int bufferSize = 1000;
    char text[bufferSize] = "";  // Inicjalizacja zmiennej "text" pustym ciągiem znaków
    char input[bufferSize];
    bool isCssMode = true;

    while (fgets(input, bufferSize, stdin) != NULL) {
        if (stringCompare(input, "????\n")) {
            // Przetworz css
            parseCss(text, Blocks, block_counter, T);

            // Wyczyść text
             stringCopy(text, "");
            
            //zacznij przetwarzac komendy 
            parseCommands(Blocks, block_counter);
        }
        else {
            // Dopisuj input do text do momentu komendy ????
            int textLength = stringLength(text);
            int inputLength = stringLength(input);
            stringCopy(text + textLength, input);
        }
    }

    return 0;
}