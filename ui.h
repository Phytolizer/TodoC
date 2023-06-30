#ifndef UI_H_
#define UI_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef size_t Id;

struct AttrPair
{
	const char* on;
	const char* off;
};

extern const struct AttrPair regular_pair;
extern const struct AttrPair highlight_pair;

struct Ui
{
	bool in_list;
	Id list_curr;
	size_t row;
	size_t col;
};

extern void UiBegin(struct Ui* ui, size_t row, size_t col);
extern void UiBeginList(struct Ui* ui, Id id);
extern void UiListElement(struct Ui* ui, const char* text, Id id);
extern void UiLabel(struct Ui* ui, const char* text, struct AttrPair pair);
extern void UiEndList(struct Ui* ui);
extern void UiEnd(struct Ui* ui);

#endif // UI_H_
