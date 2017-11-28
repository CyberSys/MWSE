/************************************************************************
	
	xFileWriteLong.cpp - Copyright (c) 2008 The MWSE Project
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
#include "FileUtil.h"

using namespace mwse;

namespace mwse
{
	class xFileWriteLong : mwse::InstructionInterface_t
	{
	public:
		xFileWriteLong();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xFileWriteLongOpcode = 0x3C32;
	static xFileWriteLong xFileWriteLongInstance;

	xFileWriteLong::xFileWriteLong() : mwse::InstructionInterface_t(xFileWriteLongOpcode) {}

	void xFileWriteLong::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xFileWriteLong::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		if (mwse::Stack::getInstance().size() < 2) {
			mwse::log::getLog() << "xFileWriteLong: Function called with too few arguments." << std::endl;
			return 0.0f;
		}

		mwseString_t fileName = virtualMachine.getString(mwse::Stack::getInstance().popLong());
		mwLong_t value = mwse::Stack::getInstance().popLong();

		mwse::FileSystem::getInstance().writeLong(fileName.c_str(), value);

		return 0.0f;
	}
}