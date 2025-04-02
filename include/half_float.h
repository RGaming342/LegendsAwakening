#pragma once

#include <cstdint>
#include <iostream>

class HalfFloat {// int(0-63) float(0-999)
	private:
		int16_t bits; // 16-bit storage
		
		static constexpr int FRACTIONAL_BITS = 9;
	public:
		HalfFloat() : bits(0) {}
		HalfFloat(float f) { *this = fromFloat(f); }
		HalfFloat(int i) { *this = fromInt(i); }
		
		HalfFloat(const HalfFloat& other) : bits(other.bits) {}
		HalfFloat& operator=(const HalfFloat& other) {
			if (this != &other) {
				bits = other.bits;
			}
			return *this;
		}
		HalfFloat(HalfFloat&& other) noexcept : bits(other.bits) {
			other.bits = 0;
		}
		HalfFloat& operator=(HalfFloat&& other) noexcept {
			if (this != &other) {
				bits = other.bits;
				other.bits = 0;
			}
			return *this;
		}
		
		static HalfFloat fromFloat(float f) {
			int sign = (f < 0) ? 1 : 0;
			f = std::abs(f);
			int intPart = static_cast<int>(f);
			int fracPart = static_cast<int>((f - intPart) * 1000.0f);
			
			if (intPart > 63) { // overflow
				intPart = 63;
				fracPart = 999;
			}
			
			int16_t encoded = (sign << 15) | (intPart << FRACTIONAL_BITS) | fracPart;
			return HalfFloat(encoded, true);
		}
		
		static HalfFloat fromInt(int i) {
			return fromFloat(static_cast<float>(i));
		}
		
		float toFloat() const {
			int sign = (bits & 0x8000) ? -1 : 1;
			int intPart = (bits >> FRACTIONAL_BITS) & 0x3F;
			int fracPart = bits & 0x1FF;
			return sign * (intPart + (fracPart / 1000.0f));
		}
		
		int toInt() const {
			return static_cast<int>(toFloat());
		}
		
		HalfFloat operator+(HalfFloat other) const {
			return fromFloat(this->toFloat() + other.toFloat());
		}
		
		HalfFloat operator-(HalfFloat other) const {
			return fromFloat(this->toFloat() - other.toFloat());
		}
		
		HalfFloat operator*(HalfFloat other) const {
			return fromFloat(this->toFloat() * other.toFloat());
		}
		
		HalfFloat operator/(HalfFloat other) const {
			if (other.toFloat() == 0) return 0;
			return fromFloat(this->toFloat() / other.toFloat());
		}
		
		bool operator==(HalfFloat other) const { return bits == other.bits; }
		bool operator!=(HalfFloat other) const { return bits != other.bits; }
		bool operator<(HalfFloat other) const { return toFloat() < other.toFloat(); }
		bool operator>(HalfFloat other) const { return toFloat() > other.toFloat(); }
		bool operator<=(HalfFloat other) const { return toFloat() <= other.toFloat(); }
		bool operator>=(HalfFloat other) const { return toFloat() >= other.toFloat(); }
		
		friend std::ostream& operator<<(std::ostream& os, const HalfFloat& h) {
			return os << h.toFloat();
		}
		int16_t getRaw(){
			return bits;
		}
		void setRaw(int16_t b){
			bits = b;
		}
	private:
		// Private constructor to set raw bits directly
		HalfFloat(int16_t raw, bool) : bits(raw) {}
};
