#ifndef DIALOGUE_H
#define DIALOGUE_H
typedef struct {
    TriggerType trigger;
    bool auto_scroll; //True for dialog that scrolls automatically, false if it requires user input to scroll
    bool bold; //Will be true for text containing critical information
    bool fired;
int trigger_time;
    int text_id; //Each string of text will be given its own unique id   
}dialogue_entry;
extern dialogue_entry dialogue_table_1[];
#endif