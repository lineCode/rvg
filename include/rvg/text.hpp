// Copyright (c) 2018 nyorain
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt

#pragma once

#include <rvg/fwd.hpp>
#include <rvg/deviceObject.hpp>
#include <rvg/font.hpp>
#include <rvg/stateChange.hpp>

#include <nytl/vec.hpp>
#include <nytl/rect.hpp>

#include <vpp/descriptor.hpp>
#include <vpp/sharedBuffer.hpp>

#include <string>
#include <string_view>

namespace rvg {

/// Represents text to be drawn.
/// Also offers some utility for bounds querying.
class Text : public DeviceObject {
public:
	Text() = default;
	Text(Context&, Vec2f pos, std::string_view text, Font&, unsigned height);
	Text(Context&, Vec2f pos, std::u32string text, Font&, unsigned height);

	Text(Text&& rhs) noexcept;
	Text& operator=(Text&& rhs) noexcept;
	~Text();

	/// Draws this text with the bound draw resources (transform,
	/// scissor, paint).
	void draw(vk::CommandBuffer) const;

	auto change() { return StateChange {*this, state_}; }
	bool disable(bool);
	bool disabled() const { return disable_; }

	/// Changes the device local state for this text.
	/// If unequal the previous value, will always recreate the buffer and
	/// trigger a rerecord.
	void deviceLocal(bool set);
	bool deviceLocal() const { return deviceLocal_; }

	/// Computes which char index lies at the given relative x.
	/// Returns the index of the char at the given x, or the index of
	/// the next one if there isn't any. Returns text.length() if x is
	/// after all chars.
	unsigned charAt(float x) const;

	// TODO
	/// Returns the bounds of the full text
	// Rect2f bounds() const;

	// TODO: broken
	/// Returns the bounds of the ith char in local coordinates.
	/// For a char that has no x-size (e.g. space), returns xadvance
	/// as x size.
	Rect2f ithBounds(unsigned n) const;

	const auto& font() const { return *state_.font; }
	const auto& utf32() const { return state_.utf32; }
	const auto& position() const { return state_.position; }
	float height() const { return state_.height; }
	auto utf8() const { return state_.utf8(); }
	float width() const;

	void update();
	bool updateDevice();

protected:
	struct State {
		std::u32string utf32 {};
		Font* font {};
		Vec2f position {};
		unsigned height {};

		void utf8(std::string_view);
		std::string utf8() const;
	} state_;

	bool disable_ {};
	bool deviceLocal_ {false};

	std::vector<Vec2f> posCache_;
	std::vector<Vec2f> uvCache_;
	vpp::SubBuffer posBuf_;
	vpp::SubBuffer uvBuf_;
	FontAtlas* oldAtlas_ {};
};

} // namespace rvg
