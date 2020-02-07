#pragma once

namespace MiniSTL {
	struct max_type{};
	struct min_type{};
	template<typename T>
	struct less {
		typedef min_type type;
		bool operator()(T& a, T& b) {
			return a < b;
		}
	};
	template<typename T>
	struct greater {
		typedef max_type type;
		bool operator()(T& a, T& b) {
			return a > b;
		}
	};
}