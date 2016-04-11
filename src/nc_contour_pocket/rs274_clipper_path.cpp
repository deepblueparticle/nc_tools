/* 
 * Copyright (C) 2016  Nicholas Gill
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
 * rs274_clipper_path.cpp
 *
 *  Created on: 2016-04-07
 *      Author: nicholas
 */

#include "rs274_clipper_path.h"
#include "Path.h"

using namespace ClipperLib;


void rs274_clipper_path::_rapid(const Position&) {
    if (path_.empty() || !path_.back().empty())
        path_.emplace_back();
}
void rs274_clipper_path::_arc(const Position& end, const Position& center, const cxxcam::math::vector_3& plane, int rotation) {
    using cxxcam::units::length_mm;

    if (plane.z != 1)
        throw std::runtime_error("Arc must exist in XY plane");
    if (std::abs(end.z - program_pos.z) > 0)
        throw std::runtime_error("Helix not supported in path");

    using namespace cxxcam::path;
	auto steps = expand_arc(convert(program_pos), convert(end), convert(center), (rotation < 0 ? ArcDirection::Clockwise : ArcDirection::CounterClockwise), plane, std::abs(rotation), {}).path;

    if (path_.empty())
        path_.emplace_back();
    for (auto& step : steps) {
        auto& p = step.position;
        path_.back().push_back(scale_point(p));
    }
}


void rs274_clipper_path::_linear(const Position& pos) {
    using cxxcam::units::length_mm;

    if (_active_plane != Plane::XY)
        throw std::runtime_error("Path must be described in XY plane");
    if (std::abs(pos.z - program_pos.z) > 0)
        throw std::runtime_error("Path must be 2d");

	auto steps = cxxcam::path::expand_linear(convert(program_pos), convert(pos), {}, -1).path;

    if (path_.empty())
        path_.emplace_back();
    for (auto& step : steps) {
        auto& p = step.position;
        path_.back().push_back(scale_point(p));
    }
}

rs274_clipper_path::rs274_clipper_path()
 : rs274_base() {
}

IntPoint rs274_clipper_path::scale_point(const cxxcam::math::point_3& p) const {
    using cxxcam::units::length_mm;
    return IntPoint(length_mm(p.x).value() * scale(), length_mm(p.y).value() * scale());
}

Paths rs274_clipper_path::path() const {
    return path_;
}