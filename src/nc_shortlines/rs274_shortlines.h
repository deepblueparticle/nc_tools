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
 * rs274_shortlines.h
 *
 *  Created on: 2016-04-06
 *      Author: nicholas
 */

#ifndef RS274_SHORTLINES_H_
#define RS274_SHORTLINES_H_
#include "base/rs274_base.h"

class rs274_shortlines : public rs274_base
{
private:
    virtual void _rapid(const Position& pos);
    virtual void _arc(const Position& end, const Position& center, const cxxcam::math::vector_3& plane, int rotation);
    virtual void _linear(const Position& pos);

    void output_point(const cxxcam::math::point_3& p, bool rapid) const;

public:
	rs274_shortlines(boost::program_options::variables_map& vm);
	virtual ~rs274_shortlines() = default;
};

#endif /* RS274_SHORTLINES_H_ */
