/* gravifon_scrobbler - an audio track scrobbler to Gravifon plugin to the audio player DeaDBeeF.
Copyright (C) 2013-2014 Dźmitry Laŭčuk

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */
#ifndef SCROBBLER_INFO_HPP_
#define SCROBBLER_INFO_HPP_

#include <cassert>
#include <string>
#include <vector>
#include <afc/dateutil.hpp>

// All strings are utf8-encoded.
class Track
{
public:
	void setTitle(const std::string &trackTitle) { m_title = trackTitle; m_titleSet = true; }
	std::string &getTitle() noexcept { assert(m_titleSet); return m_title; }
	const std::string &getTitle() const noexcept { assert(m_titleSet); return m_title; }
	bool hasTitle() const noexcept { return m_titleSet; }

	void addArtist(const std::string &artist) { m_artists.emplace_back(artist); }
	std::vector<std::string> &getArtists() noexcept { return m_artists; }
	const std::vector<std::string> &getArtists() const noexcept { return m_artists; }
	bool hasArtist() const noexcept { return !m_artists.empty(); }

	void addAlbumArtist(const std::string &artist) { m_albumArtists.emplace_back(artist); }
	std::vector<std::string> &getAlbumArtists() noexcept { return m_albumArtists; }
	const std::vector<std::string> &getAlbumArtists() const noexcept { return m_albumArtists; }
	bool hasAlbumArtist() const noexcept { return !m_albumArtists.empty(); }

	void setAlbumTitle(const std::string &albumTitle) { m_album = albumTitle; m_albumSet = true; }
	std::string &getAlbumTitle() noexcept { assert(m_albumSet); return m_album; }
	const std::string &getAlbumTitle() const noexcept { assert(m_albumSet); return m_album; }
	bool hasAlbumTitle() const noexcept { return m_albumSet; }

	void setDurationMillis(const long duration) { m_duration = duration; m_durationSet = true; }
	long getDurationMillis() const noexcept { assert(m_durationSet); return m_duration; }
	bool hasDurationMillis() const noexcept { return m_durationSet; }

	// Appends this ScrobbleInfo in the JSON format to a given string.
	void appendAsJsonTo(std::string &str) const;
private:
	std::string m_title;
	std::vector<std::string> m_artists;
	std::vector<std::string> m_albumArtists;
	std::string m_album;
	// Track duration in milliseconds.
	long m_duration;
	bool m_titleSet = false;
	bool m_albumSet = false;
	bool m_durationSet = false;
};

struct ScrobbleInfo
{
	ScrobbleInfo() = default;
	ScrobbleInfo(const ScrobbleInfo &) = default;
	ScrobbleInfo(ScrobbleInfo &&) = default;

	ScrobbleInfo &operator=(const ScrobbleInfo &) = default;
	ScrobbleInfo &operator=(ScrobbleInfo &&) = default;

	static bool parse(const std::string &str, ScrobbleInfo &dest);

	// Date and time when scrobble event was initiated.
	afc::DateTime scrobbleStartTimestamp;
	// Date and time when scrobble event was finished.
	afc::DateTime scrobbleEndTimestamp;
	// Scrobble length in milliseconds.
	long scrobbleDuration;
	// Track to scrobble.
	Track track;

	// Appends this ScrobbleInfo in the JSON format to a given string.
	void appendAsJsonTo(std::string &str) const;
};

#endif /* SCROBBLER_INFO_HPP_ */