#ifndef MODEST_TEXT_H
#define MODEST_TEXT_H

/*
 Copyright (C) 2019 Frank Eickhoff
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

/**
 * Get the text for the first element in html string
 * @param  html  [a html string]
 * @return value [the text]
 */
const char* modest_get_text(const char* html);

/**
 * Get the text for the selected element in html string
 * @param  html     [a html string]
 * @param  selector [a CSS selector]
 * @return value    [the text]
 */
const char* modest_select_and_get_text(const char* html, const char* selector);

/**
 * Set text for the first element in html string
 * @param  html  [a html string]
 * @param  text  [the text]
 * @return       [updated html string]
 */
const char* modest_set_text(const char* html, const char* text);

/**
 * Set text for the selected element in html string
 * @param  html     [a html string]
 * @param  selector [a CSS selector]
 * @param  text     [the text]
 * @return          [updated html string]
 */
const char* modest_select_and_set_text(const char* html, const char* selector, const char* text);

#endif