#pragma once
namespace xc{
	namespace particlesystem{
		template<typename PStruct>
		class PBaseUpdator{
		public:
			void update(PStruct& src,f32 delta){
				src.life += delta;
				src.pos = src.pos + src.dir * src.speed * delta;
			}
		};
	}
}