#ifndef CORE_AI_BT_SEQUENCE_H
#define CORE_AI_BT_SEQUENCE_H

#include "bt_composite.h"

namespace core::ai {
		class Sequence : public Composite {

		public:
			Status Tick() override;
		};
}

#endif //CORE_AI_BT_SEQUENCE_H
