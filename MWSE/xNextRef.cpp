/************************************************************************
	
	xNextRef.cpp - Copyright (c) 2008 The MWSE Project
	http://www.sourceforge.net/projects/mwse

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
	
**************************************************************************/

#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"

using namespace mwse;

namespace mwse
{
	class xNextRef : mwse::InstructionInterface_t
	{
	public:
		xNextRef();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xNextRefOpcode = 0x3C1B;
	static xNextRef xNextRefInstance;

	xNextRef::xNextRef() : mwse::InstructionInterface_t(xNextRefOpcode) {}

	void xNextRef::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xNextRef::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		// Get REFR pointer as an argument.
		REFRRecord_t* reference = (REFRRecord_t*)mwse::Stack::getInstance().popLong();

		// Start looking for our next reference.
		REFRRecord_t* next = NULL;
		if (reference) {
			// Try to get the next non-removed reference linked down from the passed one.
			next = mwse::tes3::skipRemovedReferences(reference->nextRecord);

			// If we found nothing, check the stored exterior references.
			if (next == NULL && mwse::tes3::exteriorRefs[0] != NULL) {
				next = mwse::tes3::exteriorRefs[0];
				for (int i = 0; i < 8; i++) {
					mwse::tes3::exteriorRefs[i] = mwse::tes3::exteriorRefs[i + 1];
				}
			}
		}
		else {
			mwse::log::getLog() << "xNextRef: Null argument." << std::endl;
		}

		mwse::Stack::getInstance().pushLong((mwLong_t)next);

		return 0.0;
	}
}