#ifndef __UI_H_INCLUDED__
#define __UI_H_INCLUDED__

#include "Struct.h"

void resizeConsole(int width, int height);
void setScreenBufferSize(SHORT width, SHORT height);
void setWindowSize(SHORT width, SHORT height);

void txtColor(int color);
void gotoxy(int x, int y);
void UnNocursortype();
void Nocursortype();
void txtColor(int color);
void setWindowFullSize();

void logo_moodle();
void loginUI();
void keyboardShortcutMenu();
void keyboardShortcut();
void fillBlackMenu();
void fillBlackUserPass();
void drawBorderMenuStaff();
void drawBorderMenuStudent();

#endif