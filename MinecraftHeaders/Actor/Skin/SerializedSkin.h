#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "AnimatedImageData.h"
#include "SerializedPersonaPieceHandle.h"
#include "persona.h"
#include "TintMapColor.h"
#include "../../Core/Color.h"
#include "../../Core/mce.h"
#include "../../Core/json.h"
#include "../../dll.h"

class ConnectionRequest;
class SubClientConnectionRequest;
class ReadOnlyBinaryStream;
class BinaryStream;

class SerializedSkin {
public:
  std::string skin_id, name, skin_resource_patch, geometry_name;
  mce::Image texture, cape_texture;
  std::vector<AnimatedImageData> animated_imge_data;
  Json::Value geometry_data, geometry_data_mutable;
  std::string animateion_data, cape_id;
  bool premium_skin, persona_skin, cape_on_classic_skin;
  enum struct TrustedFlag : char { UNSET, NO, YES } trusted_flag;
  std::vector<SerializedPersonaPieceHandle> appearance;
  std::string appearance_name;
  std::unordered_map<PieceType, TintMapColor> colormap;
  Color skin_color;

#pragma region methods
  MCAPI SerializedSkin();
  MCAPI SerializedSkin(SerializedSkin const &);
  MCAPI SerializedSkin(ConnectionRequest const &);
  MCAPI SerializedSkin(SubClientConnectionRequest const &);

  MCAPI SerializedSkin &operator=(SerializedSkin const &);

  MCAPI void read(ReadOnlyBinaryStream &);
  MCAPI void write(BinaryStream &);
  MCAPI void updateGeometryName();

  inline std::string const &getName() const { return name; }
  inline bool getIsPersona() const { return persona_skin; }
  inline Json::Value const &getGeometryData() const { return geometry_data; }
  inline Json::Value const &getGeometryDataMutable() const { return geometry_data_mutable; }
  inline mce::Image const &getCapeImageData() const { return cape_texture; }
  inline bool isTrustedSkin() const { return trusted_flag == TrustedFlag::YES; }
  inline Color const &getSkinColor() { return skin_color; }

  inline void setCapeId(std::string const &str) {
    cape_id = str;
    name    = skin_id + str;
  }

  inline void setCapeImageData(mce::Image const *ptr) {
    if (ptr)
      cape_texture = ptr->clone();
    else
      cape_texture = {};
  }

  inline void setImageData(mce::Image const *ptr) {
    if (ptr)
      texture = ptr->clone();
    else
      texture = {};
  }

  inline bool setIsPersonaCapeOnClassicSkin(bool value) { return cape_on_classic_skin = value; }

  inline float getAnimationFrames(AnimatedTextureType type) const {
    for (auto &item : animated_imge_data) {
      if (item.type == type) return item.frame;
    }
    return 1.0f;
  }
#pragma endregion
};

static_assert(offsetof(SerializedSkin, premium_skin) == 312);
static_assert(offsetof(SerializedSkin, persona_skin) == 313);
static_assert(offsetof(SerializedSkin, trusted_flag) == 315);
static_assert(offsetof(SerializedSkin, appearance) == 320);
static_assert(offsetof(SerializedSkin, appearance_name) == 344);
static_assert(offsetof(SerializedSkin, colormap) == 376);
static_assert(offsetof(SerializedSkin, skin_color) == 440);