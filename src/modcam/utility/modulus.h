/*
 * Copyright 2023 prosilio
 *
 * This file is part of modCAM, open source software for Computer Aided
 * Manufacturing research.
 *
 * modCAM is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * modCAM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * modCAM. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MODULUS_H
#define MODULUS_H

namespace modcam::utility {
// Modulo function for looping backward
// For example, mod(-1, 3) == 2, whereas -1 % 3 == -1
template <typename T> T mod(T k, T n) { return ((k %= n) < 0) ? k + n : k; }
} // namespace modcam::utility

#endif
