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
 * rs274_bounds.cpp
 *
 *  Created on: 2015-07-24
 *      Author: nicholas
 */

#include "rs274_bounds.h"
#include <cmath>
#include <cstring>
#include "throw_if.h"
#include "fold_adjacent.h"
#include <algorithm>
#include "Path.h"

cxxcam::math::point_3 pos2point(const cxxcam::Position& pos) {
    return {pos.X, pos.Y, pos.Z};
}

void rs274_bounds::_rapid(const Position& pos) {
    if (track_rapid) {
        bbox += pos2point(convert(program_pos));
        bbox += pos2point(convert(pos));
    }
}

void rs274_bounds::_arc(const Position& end, const Position& center, const cxxcam::math::vector_3& plane, int rotation) {
    using namespace cxxcam::path;
    if (track_cut) {
        auto steps = expand_arc(convert(program_pos), convert(end), convert(center), (rotation < 0 ? ArcDirection::Clockwise : ArcDirection::CounterClockwise), plane, std::abs(rotation), {}).path;

        for (auto& step : steps)
            bbox += step.position;
    }
}


void rs274_bounds::_linear(const Position& pos) {
    if (track_cut) {
        bbox += pos2point(convert(program_pos));
        bbox += pos2point(convert(pos));
    }
}

rs274_bounds::rs274_bounds(bool cut, bool rapid)
 : rs274_base(), track_cut(cut), track_rapid(rapid) {
}

cxxcam::Bbox rs274_bounds::bounding_box() const {
    return bbox;
}