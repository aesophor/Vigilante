// Copyright (c) 2018-2021 Marco Wang <m.aesophor@gmail.com>. All rights reserved.
#include "AmountSelectionWindow.h"

#include "std/make_unique.h"
#include "AssetManager.h"
#include "character/Player.h"
#include "input/InputManager.h"
#include "util/StringUtil.h"

#define AMOUNT_SELECTION_WINDOW_CONTENT_MARGIN_LEFT 10
#define AMOUNT_SELECTION_WINDOW_CONTENT_MARGIN_RIGHT 10
#define AMOUNT_SELECTION_WINDOW_CONTENT_MARGIN_TOP 5
#define AMOUNT_SELECTION_WINDOW_CONTENT_MARGIN_BOTTOM 15

using std::string;
using std::function;
using cocos2d::Size;
using cocos2d::ui::Layout;
using cocos2d::ui::ImageView;
using cocos2d::EventKeyboard;
using vigilante::asset_manager::kTextFieldBg;

namespace vigilante {

AmountSelectionWindow::AmountSelectionWindow()
    : Window(),
      _contentBackground(ImageView::create(kTextFieldBg)),
      _textField("1") {

  setTitle("How many?");
  Size windowSize = _titleLabel->getContentSize();
  windowSize.width = std::max(windowSize.width, _contentBackground->getContentSize().width);
  windowSize.height += _contentBackground->getContentSize().height;
  windowSize.width += AMOUNT_SELECTION_WINDOW_CONTENT_MARGIN_LEFT;
  windowSize.width += AMOUNT_SELECTION_WINDOW_CONTENT_MARGIN_RIGHT;
  windowSize.height += AMOUNT_SELECTION_WINDOW_CONTENT_MARGIN_TOP;
  windowSize.height += AMOUNT_SELECTION_WINDOW_CONTENT_MARGIN_BOTTOM;
  resize(windowSize);

  _contentBackground->setAnchorPoint({0, 1});
  _contentBackground->setPosition({0, 15});

  _contentLayout->setLayoutType(Layout::Type::ABSOLUTE);
  _contentLayout->setAnchorPoint({0, 1});
  _contentLayout->addChild(_contentBackground, 0);

  // Place the text field
  _textField.getLayout()->setPosition({5, 0});
  _contentLayout->addChild(_textField.getLayout(), 1);

  update(0);
}

AmountSelectionWindow::~AmountSelectionWindow() {
  if (_textField.isReceivingInput()) {
    _textField.setReceivingInput(false);
  }
}


void AmountSelectionWindow::update(float delta) {
  _textField.update(delta);
}

void AmountSelectionWindow::handleInput() {

}


TextField* AmountSelectionWindow::getTextField() {
  return &_textField;
}

}  // namespace vigilante
