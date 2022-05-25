#ifndef ADDRESS_H
#define ADDRESS_H

#include <bitset>
#include <cstdint>

namespace sic
{
	//address object used in format 3 and 4 instructions
	class Address
	{
		private:
			uint32_t m_display = 0;
			std::bitset<6> m_nixbpe;
		public:
			Address()
			{
				m_nixbpe.set();
			}
			Address(uint32_t display,
				bool indirect,
				bool immediate,
				bool indexed,
				bool baseRelative,
				bool pcRelative,
				bool extended) : m_display{display}
			{
				m_nixbpe[5] = indirect;
				m_nixbpe[4] = immediate;
				m_nixbpe[3] = indexed;
				m_nixbpe[2] = baseRelative;
				m_nixbpe[1] = pcRelative;
				m_nixbpe[0] = extended;
			}

			inline uint8_t nixbpe()
			{
				return m_nixbpe.to_ulong();
			}
			inline uint32_t display()
			{
				return m_display;
			}
			inline bool indirect()
			{
				return m_nixbpe.test(5);
			}
			inline bool immediate()
			{
				return m_nixbpe.test(4);
			}
			inline bool indexed()
			{
				return m_nixbpe.test(3);
			}
			inline bool baseRelative()
			{
				return m_nixbpe.test(2);
			}
			inline bool pcRelative()
			{
				return m_nixbpe.test(1);
			}
			inline bool extended()
			{
				return m_nixbpe.test(0);
			}

	};
}
#endif
