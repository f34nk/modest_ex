#ifndef MODEST_SLICE_H
#define MODEST_SLICE_H

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
 * Slice set into two subsets. First set from first node until selected node. Second set from selected node to end.
 * @param  html      [a html string]
 * @param  selector  [a CSS selector]
 * @param  delimiter [delimiter string]
 * @param  scope     [scope string]
 * @return           [updated html string]
 */
const char* modest_slice_until_selected(const char* html, const char* selector, const char* delimiter, const char* scope);

#endif