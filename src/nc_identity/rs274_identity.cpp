/* 
 * Copyright (C) 2013  Nicholas Gill
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * rs274_identity.cpp
 *
 *  Created on: 2015-11-12
 *      Author: nicholas
 */

#include "rs274_identity.h"
#include <iostream>
#include <iomanip>
#include <sstream>

std::string r6(double v) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(6) << v;
    auto s = ss.str();
    
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if(s.back() == '.') s.pop_back();
    return s;
}

void rs274_identity::_rapid(const Position&) {
}

void rs274_identity::_arc(const Position&, const Position&, const cxxcam::math::vector_3&, int) {
}


void rs274_identity::_linear(const Position&) {
}

rs274_identity::rs274_identity()
 : rs274_base() {
}

