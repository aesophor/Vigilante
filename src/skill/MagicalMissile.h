// Copyright (c) 2019 Marco Wang <m.aesophor@gmail.com>. All rights reserved.
#ifndef VIGILANTE_MAGICAL_MISSILE_H_
#define VIGILANTE_MAGICAL_MISSILE_H_

#include <string>

#include <Box2D/Box2D.h>
#include <cocos2d.h>
#include "DynamicActor.h"
#include "Projectile.h"
#include "Skill.h"

namespace vigilante {

class Character;

class MagicalMissile : public DynamicActor, public Skill, public Projectile {
 public:
  MagicalMissile(const std::string& jsonFileName, Character* user);
  virtual ~MagicalMissile() = default;

  virtual void showOnMap(float x, float y) override;  // DynamicActor
  virtual void update(float delta) override;          // DynamicActor

  virtual Character* getUser() const override;     // Projectile
  virtual int getDamage() const override;          // Projectile
  virtual void onHit(Character* target) override;  // Projectile

  virtual void import(const std::string& jsonFileName) override;            // Skill
  virtual cocos2d::EventKeyboard::KeyCode getHotkey() const override;       // Skill
  virtual void setHotkey(cocos2d::EventKeyboard::KeyCode hotkey) override;  // Skill
  virtual bool canActivate() override;                                      // Skill
  virtual void activate() override;                                         // Skill

  virtual Skill::Profile& getSkillProfile() override;   // Skill
  virtual const std::string& getName() const override;  // Skill
  virtual const std::string& getDesc() const override;  // Skill
  virtual std::string getIconPath() const override;     // Skill

 private:
  virtual void defineBody(b2BodyType bodyType, short categoryBits, short maskBits, float x,
                          float y);
  virtual void defineTexture(const std::string& textureResPath, float x, float y);

  Skill::Profile _skillProfile;
  Character* _user;
  float _flyingSpeed;
  bool _hasActivated;
  bool _hasHit;

  cocos2d::Sprite* _launchFxSprite;  // sprite of launching fx

  enum AnimationType { LAUNCH_FX, FLYING, ON_HIT, SIZE };
};

}  // namespace vigilante

#endif  // VIGILANTE_MAGICAL_MISSILE_H_