#ifndef MODEST_ATTRIBUTE_H
#define MODEST_ATTRIBUTE_H
// #include "utils.h"
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
 * Get the value of an attribute for the first element in html string
 * @param  html  [a html string]
 * @param  key  [key of the attribute]
 * @param  delimiter  [string]
 * @return value [value of the attribute]
 */
const char* modest_get_attribute(const char* html, const char* key, const char* delimiter);

/**
 * Get the value of an attribute for the selected element in html string
 * @param  html     [a html string]
 * @param  selector [a CSS selector]
 * @param  key     [key of the attribute]
 * @param  delimiter  [string]
 * @return value    [value of the attribute]
 */
const char* modest_select_and_get_attribute(const char* html, const char* selector, const char* key, const char* delimiter);

/**
 * Set the value of an attribute for the first element in html string
 * @param  html  [a html string]
 * @param  key  [key of the attribute]
 * @param  value [value of the attribute]
 * @return       [updated html string]
 */
const char* modest_set_attribute(const char* html, const char* key, const char* value);

/**
 * Set the value of an attribute for the selected element in html string
 * @param  html     [a html string]
 * @param  selector [a CSS selector]
 * @param  key     [key of the attribute]
 * @param  value    [value of the attribute]
 * @return          [updated html string]
 */
const char* modest_select_and_set_attribute(const char* html, const char* selector, const char* key, const char* value);

#endif