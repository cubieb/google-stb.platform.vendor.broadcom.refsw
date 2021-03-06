/******************************************************************************
 *   (c)2011-2012 Broadcom Corporation
 *
 * This program is the proprietary software of Broadcom Corporation and/or its
 * licensors, and may only be used, duplicated, modified or distributed
 * pursuant to the terms and conditions of a separate, written license
 * agreement executed between you and Broadcom (an "Authorized License").
 * Except as set forth in an Authorized License, Broadcom grants no license
 * (express or implied), right to use, or waiver of any kind with respect to
 * the Software, and Broadcom expressly reserves all rights in and to the
 * Software and all intellectual property rights therein.  IF YOU HAVE NO
 * AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY,
 * AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE
 * SOFTWARE.  
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1.     This program, including its structure, sequence and organization,
 * constitutes the valuable trade secrets of Broadcom, and you shall use all
 * reasonable efforts to protect the confidentiality thereof, and to use this
 * information only in connection with your use of Broadcom integrated circuit
 * products.
 *
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED
 * "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL
 * IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR
 * A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE
 * ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
 * ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
 * INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY
 * RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN
 * EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1,
 * WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY
 * FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
 *****************************************************************************/

#ifndef __LOGO_MENU_H__
#define __LOGO_MENU_H__

#include "bsg_application.h"
#include "bsg_animatable.h"
#include "bsg_animator.h"
#include "bsg_font.h"
#include "bsg_text.h"

#include "../common/bcm_backdrop.h"
#include "../common/bcm_guilloche.h"
#include "../common/bcm_help_menu.h"

#include "menu_carousel.h"

namespace bsg
{
   class SceneNode;
   class Camera;
}

class MenuItem
{
public:
   std::string textureFile;
   std::string quickText;
   std::string desc;
   std::string folder;
   std::string exe;
   std::string args;
   bool        enabled;
};

class BCMGuilloche
{
public:
   BCMGuilloche(bsg::Application &app);

   void Render();
   void UpdateAnimationList(const bsg::Time &now);

private:
   bsg::Application     &m_app;
   uint32_t             m_numControls;
   Guilloche            m_guilloche;
   GuillochePanel       m_guillochePanel;
   bsg::AnimationList   m_animList;
};

class ParseArgs;

class LogoMenu : public bsg::Application
{
public:
   LogoMenu(bsg::Platform &platform, const ParseArgs &args);

   void WriteDemoScript(uint32_t current);

private:
   // Overridden methods
   virtual bool UpdateFrame(int32_t *idleMs);
   virtual void RenderFrame();
   virtual void KeyEventHandler(bsg::KeyEvents &queue);
   virtual void MouseEventHandler(bsg::MouseEvents &queue);
   virtual void ResizeHandler(uint32_t width, uint32_t height);

   // Private methods
   bool LoadMenu(const std::string &file, uint32_t startAt);
   bsg::MaterialHandle MakeEnvMappedMaterial(bsg::EffectHandle effect, bsg::TextureHandle irrad, 
                                        bsg::TextureHandle refl, bsg::TextureHandle occlusion, 
                                        const bsg::Vec4 &color, float dimScale);
   void DrawTime(const bsg::Vec2 &pos);
   void HandleSpecialMenuCases(MenuItem *item);

   bool ParseOriginalFormat(FILE *fp, std::vector<char> &buff, std::vector<MenuItem> &menuItems);
   bool ParseMultiFormat(FILE *fp, std::vector<char> &buff, std::vector<MenuItem> &menuItems);

private:
   bsg::SceneNodeHandle    m_carouselRoot;
   bsg::SceneNodeHandle    m_logoRoot;
   //bsg::SceneNodeHandle m_backdropRoot;
   uint32_t                m_startAt;

   bsg::SceneNodeHandle    m_carouselCamNode;
   bsg::CameraHandle       m_carouselCamera;

   bsg::SceneNodeHandle    m_logoCamNode;
   bsg::CameraHandle       m_logoCamera;

   bsg::AnimationList      m_animList;

   bsg::Auto<MenuCarousel> m_carousel;

   std::vector<MenuItem>   m_menuItems;
   bool                    m_multiMenu;

   bsg::FontHandle         m_font;
   bsg::FontHandle         m_smallFont;

//   BCMBackdrop             m_backdrop;
   BCMGuilloche            m_guilloche;

   HelpMenu                *m_helpMenu;

   std::string             m_configFile;
};

#endif /* __LOGO_MENU_H__ */
