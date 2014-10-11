/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * bmonkey
 * Copyright (C) 2014 Juan Ángel Moreno Fernández
 *
 * bmonkey is free software.
 *
 * You can redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * bmonkey is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bmonkey.  If not, see <http://www.gnu.org/licenses/>
 */

inline bool ControlManager::save(void)
{
	if (!m_file.empty())
	{
		return save(m_file);
	}
	else
	{
		return false;
	}
}

inline std::vector<bool> ControlManager::getEventsStatus(void) const
{
	return m_events_status;
}

inline void ControlManager::setEventsStatus(const std::vector<bool>& status)
{
	assert(m_events_status == status);
	m_events_status = status;
}

inline void ControlManager::enableEvent(const Event event)
{
	assert(event < OTHER);
	m_events_status[event] = true;
}

inline void ControlManager::disableEvent(const Event event)
{
	assert(event < OTHER);
	m_events_status[event] = false;
}

inline void ControlManager::ignoreAltKey(const bool ignore)
{
	m_ignore_alt_key = ignore;
}

inline std::string ControlManager::getAltKey(const unsigned char set) const
{
	assert(set < MAX_CONTROL_SETS);
	return m_alt_keys[set];
}

inline void ControlManager::registerAltKey(const unsigned char set, const std::string& command)
{
	assert(set < MAX_CONTROL_SETS);
	
	m_alt_keys[set] = command;
}

inline std::string ControlManager::getLastCommand(void) const
{
	return m_last_command;
}

inline std::vector<std::string> ControlManager::getControlSet(const unsigned char set) const
{
	assert(set < MAX_CONTROL_SETS);

	return m_control_sets[set];
}