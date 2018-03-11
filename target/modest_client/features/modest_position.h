#ifndef MODEST_POSITION_H
#define MODEST_POSITION_H

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
 * Get position of selected child in relation to its parent.
 * @param  html      [a html string]
 * @param  selector  [a CSS selector]
 * @param  delimiter [a delimiter string]
 * @return           [position string]
 */
const char* modest_selected_position(const char* html, const char* selector, const char* delimiter);

#endif