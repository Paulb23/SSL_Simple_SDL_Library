#include "interface.h"
#include "../misc/logger.h"
#include "../misc/list.h"
#include "../misc/sdl_color.h"
#include "../graphics/SSL_window.h"
#include "../graphics/sdl_image_draw.h"
#include <stdlib.h>


/**************************//**
 *
 * Creates a Interface an returns it
 * If it fails to create return -1
 *
 *************************/
Interface *interface_create() {
	Interface *interface = malloc(sizeof(Interface));
	if (!interface) {log_write("Failed to allocate memory for new Interface! "); return (Interface *)-1;}

	interface->buttons = list_create();
	interface->textboxes = list_create();

	return interface;
}


/**************************//**
 *
 * Adds a button without an image to the interface
 *
 * @param interface - the interface to add the button to
 * @param text_button - the text button to add to the interface
 *
 *************************/
void interface_add_text_button(Interface *interface, Text_Button *text_button) {
	list_set(interface->buttons, text_button);
}


/**************************//**
 *
 * Adds a image based button to the interface
 *
 * @param interface - the interface to add the button to
 * @param image_button - the image button to add to the interface
 *
 *************************/
void interface_add_image_button(Interface *interface, Image_Button *image_button) {
	list_set(interface->buttons, image_button);
}


/**************************//**
 *
 * Adds a image based button to the interface
 *
 * @param interface - the interface to add the button to
 * @param check_box - the check box to add to the interface
 *
 *************************/
void interface_add_check_box(Interface *interface, Check_box *check_box) {
	list_set(interface->buttons, check_box);
}


/**************************//**
 *
 * removes a button without an image from the interface
 *
 * @param interface - the interface to add the button to
 * @param text_button - the text button to remove from the interface
 *
 *************************/
void interface_remove_text_button(Interface *interface, Text_Button *text_button) {
	list_remove(interface->buttons, text_button);
}


/**************************//**
 *
 * removes a image based button from the interface
 *
 * @param interface - the interface to add the button to
 * @param image_button - the image button to remove from the interface
 *
 *************************/
void interface_remove_image_button(Interface *interface, Image_Button *image_button) {
	list_remove(interface->buttons, image_button);
}


/**************************//**
 *
 * removes a check box from the interface
 *
 * @param interface - the interface to add the button to
 * @param check_box - the check box to remove from the interface
 *
 *************************/
void interface_remove_check_box(Interface *interface, Check_box *check_box) {
	list_remove(interface->buttons, check_box);
}


/**************************//**
 *
 * draws the interface
 *
 * @param interface - the interface to draw
 * @param window - the window to draw to
 *
 *************************/
void interface_draw(Interface *interface, SSL_Window *window) {
	int i = 1;
	Text_Button * text_button;
	Image_Button * image_button;
	Check_box * check_box;

	while (list_get(interface->buttons, i) != (void *)-1) {

		text_button = list_get(interface->buttons, i);

		if (text_button->button->type == TEXT_BUTTON) {
				SDL_Color *c;
				c = (SDL_Color *)color_create(255, 255, 255, 255);
				SDL_GetRenderDrawColor(window->renderer, &c->r, &c->g, &c->b, &c->a);
				SDL_SetRenderDrawColor(window->renderer, text_button->button_text_info->background_color->r, text_button->button_text_info->background_color->g, text_button->button_text_info->background_color->b, text_button->button_text_info->background_color->a);
				SDL_RenderFillRect(window->renderer, &text_button->button->position);
				SDL_SetRenderDrawColor(window->renderer, c->r, c->g, c->b, c->a);
				font_draw(text_button->button->position.x + 5, text_button->button->position.y - 5, 0, SDL_FLIP_NONE, text_button->button_text_info->text, text_button->button_text_info->font, text_button->button_text_info->color, window);
		} else if (text_button->button->type == CHECK_BOX) {
			check_box = list_get(interface->buttons, i);

			if (check_box->check_box_status->active) {
				image_draw(check_box->button_image_info->image, check_box->button->position.x, check_box->button->position.y, 0,check_box->check_box_image_info->active_frame, SDL_FLIP_NONE, window);
			} else if (check_box->button_status->pressed) {
				image_draw(check_box->button_image_info->image, check_box->button->position.x, check_box->button->position.y, 0,check_box->button_image_info->pressed_frame, SDL_FLIP_NONE, window);
			} else if (check_box->button_status->hovered) {
				image_draw(check_box->button_image_info->image, check_box->button->position.x, check_box->button->position.y, 0,check_box->button_image_info->hovered_frame, SDL_FLIP_NONE, window);
			} else {
				image_draw(check_box->button_image_info->image, check_box->button->position.x, check_box->button->position.y, 0,check_box->button_image_info->default_frame, SDL_FLIP_NONE, window);
			}
		} else {
			image_button = list_get(interface->buttons, i);

			if (image_button->button_status->pressed) {
				image_draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->pressed_frame, SDL_FLIP_NONE, window);
			} else if (image_button->button_status->hovered) {
				image_draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->hovered_frame, SDL_FLIP_NONE, window);
			} else {
				image_draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->default_frame, SDL_FLIP_NONE, window);
			}
		}
	 i++;
	}
}


/**************************//**
 *
 * updates the interface
 *
 * @param interface - the interface to update
 * @param event - the event queue
 *
 *************************/
void interface_update(Interface *interface, SDL_Event event) {
	Text_Button *button;

	int i = 1;
	int x = event.button.x;
	int y = event.button.y;

	while (list_get(interface->buttons, i) != (void *)-1) {

		button = list_get(interface->buttons, i);

		if (( x > button->button->position.x ) && ( x < button->button->position.x + button->button->position.w ) && ( y > button->button->position.y ) && ( y < button->button->position.y + button->button->position.h )) {
				button->button_status->hovered = 1;
		} else {
				button->button_status->hovered = 0;
		}

		if (event.type == SDL_MOUSEBUTTONUP) {
			if(event.button.button == SDL_BUTTON_LEFT) {						// Left Button
				button->button_status->pressed = 0;

				if (( x > button->button->position.x ) && ( x < button->button->position.x + button->button->position.w ) && ( y > button->button->position.y ) && ( y < button->button->position.y + button->button->position.h )) {
						event.button.button = 0;
						button->button_status->clicked = 1;
				} else {
						button->button_status->clicked = 0;
				}
			} else {
				button->button_status->clicked = 0;
			}
		} else {
			button->button_status->clicked = 0;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN || button->button_status->pressed == 1) {
			if(event.button.button == SDL_BUTTON_LEFT) {						// Left Button
				if (( x > button->button->position.x ) && ( x < button->button->position.x + button->button->position.w ) && ( y > button->button->position.y ) && ( y < button->button->position.y + button->button->position.h )) {
						event.button.button = 0;
						button->button_status->pressed = 1;
				} else {
						button->button_status->pressed = 0;
				}
			} else {
				button->button_status->pressed = 0;
			}
		}

		if (button->button->type == CHECK_BOX && button->button_status->clicked) {
			Check_box *box = list_get(interface->buttons, i);
			box->check_box_status->active = !box->check_box_status->active;
			button->button_status->pressed = 0;
			button->button_status->hovered = 0;
			button->button_status->clicked = 0;
		}
	 i++;
	}
}
