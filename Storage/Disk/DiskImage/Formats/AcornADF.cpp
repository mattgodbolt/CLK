//
//  AcornADF.cpp
//  Clock Signal
//
//  Created by Thomas Harte on 25/09/2016.
//  Copyright © 2016 Thomas Harte. All rights reserved.
//

#include "AcornADF.hpp"

#include "Utility/ImplicitSectors.hpp"

namespace {
	static const int sectors_per_track = 16;
	static const int sector_size = 1;
}

using namespace Storage::Disk;

AcornADF::AcornADF(const char *file_name) : MFMSectorDump(file_name) {
	// very loose validation: the file needs to be a multiple of 256 bytes
	// and not ungainly large
	if(file_.stats().st_size % static_cast<off_t>(128 << sector_size)) throw ErrorNotAcornADF;
	if(file_.stats().st_size < 7 * static_cast<off_t>(128 << sector_size)) throw ErrorNotAcornADF;

	// check that the initial directory's 'Hugo's are present
	file_.seek(513, SEEK_SET);
	uint8_t bytes[4];
	file_.read(bytes, 4);
	if(bytes[0] != 'H' || bytes[1] != 'u' || bytes[2] != 'g' || bytes[3] != 'o') throw ErrorNotAcornADF;

	file_.seek(0x6fb, SEEK_SET);
	file_.read(bytes, 4);
	if(bytes[0] != 'H' || bytes[1] != 'u' || bytes[2] != 'g' || bytes[3] != 'o') throw ErrorNotAcornADF;

	set_geometry(sectors_per_track, sector_size, true);
}

int AcornADF::get_head_position_count() {
	return 80;
}

int AcornADF::get_head_count() {
	return 1;
}

long AcornADF::get_file_offset_for_position(Track::Address address) {
	return (address.position * 1 + address.head) * (128 << sector_size) * sectors_per_track;
}
