#pragma once

#include <iostream>
#include <ostream>
#include <chrono>

namespace labbish::message {
	class TimeMsg :public std::ostream {
	public:
		inline TimeMsg() :std::ostream(&buf) {
			buf.setColor();
		}
		inline ~TimeMsg() {
			buf.resetColor();
		}
	private:
		class TimeBuf : public std::streambuf {
		public:
			inline void setColor() {
				std::cerr << "\033[32m[TIME] Command Time Cost: ";
			}

			inline void resetColor() {
				std::cerr << "ms. \033[0m\n";
			}
			inline int overflow(int c) override {
				if (c != EOF) {
					std::cerr.put(c);
				}
				return c;
			}
		};
		TimeBuf buf;
	};

	class TimeDebugger {
		std::chrono::high_resolution_clock::time_point start, end;
		double cost;
	public:
		inline TimeDebugger() {
			start = end = std::chrono::high_resolution_clock::now();
			cost = 0;
		}
		inline void flush() {
			start = end = std::chrono::high_resolution_clock::now();
			cost = 0;
		}
		inline void debug() {
			end = std::chrono::high_resolution_clock::now();
			cost = (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000;
			TimeMsg() << cost;
			start = end;
		}
		inline double previousCost() {
			return cost;
		}
	};
}