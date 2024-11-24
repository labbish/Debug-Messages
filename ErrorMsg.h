#pragma once

#include <iostream>
#include <ostream>

namespace labbish::message {
	class ErrorMsg :public std::ostream {
	public:
		inline ErrorMsg() :std::ostream(&buf) {
			buf.setColor();
			buf.setPrefix();
		}
		inline ErrorMsg(int) : std::ostream(&buf) {
			buf.setColor();
		}
		inline ~ErrorMsg() {
			buf.resetColor();
		}
		inline static ErrorMsg no_prefix() {
			return ErrorMsg(0);
		}
	private:
		class ErrorBuf : public std::streambuf {
		public:
			inline void setColor() {
				std::cerr << "\033[31m";
			}
			inline void setPrefix() {
				std::cerr << "[ERROR] ";
			}
			inline void resetColor() {
				std::cerr << "\033[0m\n";
			}
			inline int overflow(int c) override {
				if (c != EOF) {
					std::cerr.put(c);
				}
				return c;
			}
		};
		ErrorBuf buf;
	};
}