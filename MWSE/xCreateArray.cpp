/************************************************************************
	
	xCreateArray.cpp - Copyright (c) 2008 The MWSE Project
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
#include "ArrayUtil.h"

using namespace mwse;

namespace mwse
{
	class xCreateArray : mwse::InstructionInterface_t
	{
	public:
		xCreateArray();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xCreateArrayOpcode = 0x3931;
	static xCreateArray xCreateArrayInstance;

	xCreateArray::xCreateArray() : mwse::InstructionInterface_t(xCreateArrayOpcode) {}

	void xCreateArray::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xCreateArray::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		mwLong_t id = mwse::Arrays::getInstance().create("xCreateArray");

		mwse::Stack::getInstance().pushLong(id);

		return 0.0f;
	}
}