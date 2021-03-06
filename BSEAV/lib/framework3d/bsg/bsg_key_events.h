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

#ifndef __BSG_KEY_EVENTS_H__
#define __BSG_KEY_EVENTS_H__

#include "bsg_common.h"
#include "bsg_time.h"
#include "bsg_task.h"
#include <list>

namespace bsg
{

//! Encapsulates the data about a key-press, either on the IR remote, or keyboard when simulated or emulated.
class KeyEvent
{
public:
   enum eKeyState
   {
      eKEY_STATE_UNKNOWN = 0,
      eKEY_STATE_DOWN,
      eKEY_STATE_UP,
      eKEY_STATE_REPEAT,

      eKEY_STATE_LAST_STATE
   };

   enum eKeyCode
   {
      eKEY_NONE       = 0,
      KEY_NONE        = 0,

      // IR events
      eKEY_UNKNOWN    = 1,
      eKEY_EXIT       = 2,
      eKEY_CLEAR      = 2, // Same as Exit
      eKEY_OK         = 3,
      eKEY_SELECT     = 3, // Same as OK
      eKEY_POWER      = 4,
      eKEY_VOL_UP     = 5,
      eKEY_VOL_DOWN   = 6,
      eKEY_CH_UP      = 7,
      eKEY_CH_DOWN    = 8,
      eKEY_MENU       = 9,

      // For legacy support
      KEY_UNKNOWN     = 1,
      KEY_EXIT        = 2,
      KEY_OK          = 3,
      KEY_POWER       = 4,
      KEY_VOL_UP      = 5,
      KEY_VOL_DOWN    = 6,
      KEY_CH_UP       = 7,
      KEY_CH_DOWN     = 8,
      KEY_MENU        = 9,

      // Shared keyboard / IR events
      eKEY_0          = 10,
      eKEY_1          = 11,
      eKEY_2          = 12,
      eKEY_3          = 13,
      eKEY_4          = 14,
      eKEY_5          = 15,
      eKEY_6          = 16,
      eKEY_7          = 17,
      eKEY_8          = 18,
      eKEY_9          = 19,
      eKEY_UP         = 20,
      eKEY_DOWN       = 21,
      eKEY_LEFT       = 22,
      eKEY_RIGHT      = 23,

      // For legacy support
      KEY_0           = 10,
      KEY_1           = 11,
      KEY_2           = 12,
      KEY_3           = 13,
      KEY_4           = 14,
      KEY_5           = 15,
      KEY_6           = 16,
      KEY_7           = 17,
      KEY_8           = 18,
      KEY_9           = 19,
      KEY_UP          = 20,
      KEY_DOWN        = 21,
      KEY_LEFT        = 22,
      KEY_RIGHT       = 23,

      // New IR only events
      eKEY_PICTURE,
      eKEY_ASPECT,
      eKEY_PIP,
      eKEY_SWAP,
      eKEY_APPS,
      eKEY_FUNA,
      eKEY_GUIDE,
      eKEY_REVERSE,
      eKEY_FAV1,
      eKEY_FAV2,
      eKEY_FAV3,
      eKEY_FAV4,
      eKEY_FREEZE,
      eKEY_PHOTO,
      eKEY_MUSIC,
      eKEY_SOURCE,
      eKEY_WATCHTV,
      eKEY_ENT,
      eKEY_BULLET,

      // New shared keyboard / IR events
      eKEY_RED,
      eKEY_GREEN,
      eKEY_YELLOW,
      eKEY_BLUE,
      eKEY_PLAY,
      eKEY_PAUSE,
      eKEY_STOP,
      eKEY_REWIND,
      eKEY_FASTFORWARD,
      eKEY_BACK,
      eKEY_FORWARD,
      eKEY_RECORD,
      eKEY_INFO,
      eKEY_VIDEO,
      eKEY_SUBTITLE,
      eKEY_MUTE,
      eKEY_AUDIO,
      eKEY_SLEEP,
      eKEY_LAST,
      eKEY_TEXT,

      // Keyboard only events
      eKEY_RESERVED,
      eKEY_ESC,
      eKEY_BACKSPACE,

      eKEY_A,
      eKEY_B,
      eKEY_C,
      eKEY_D,
      eKEY_E,
      eKEY_F,
      eKEY_G,
      eKEY_H,
      eKEY_I,
      eKEY_J,
      eKEY_K,
      eKEY_L,
      eKEY_M,
      eKEY_N,
      eKEY_O,
      eKEY_P,
      eKEY_Q,
      eKEY_R,
      eKEY_S,
      eKEY_T,
      eKEY_U,
      eKEY_V,
      eKEY_W,
      eKEY_X,
      eKEY_Y,
      eKEY_Z,

      eKEY_MINUS,
      eKEY_EQUAL,
      eKEY_TAB,
      eKEY_LEFTBRACE,
      eKEY_RIGHTBRACE,
      eKEY_GRAVE,
      eKEY_COMMA,
      eKEY_DOT,
      eKEY_SLASH,
      eKEY_SEMICOLON,
      eKEY_APOSTROPHE,
      eKEY_BACKSLASH,
      eKEY_SPACE,
      eKEY_KPASTERISK,
      eKEY_KPMINUS,
      eKEY_KPPLUS,
      eKEY_KPDOT,

      eKEY_ENTER,
      eKEY_LEFTCTRL,
      eKEY_LEFTSHIFT,
      eKEY_RIGHTSHIFT,
      eKEY_LEFTALT,
      eKEY_CAPSLOCK,
      eKEY_F1,
      eKEY_F2,
      eKEY_F3,
      eKEY_F4,
      eKEY_F5,
      eKEY_F6,
      eKEY_F7,
      eKEY_F8,
      eKEY_F9,
      eKEY_F10,
      eKEY_F11,
      eKEY_F12,
      eKEY_NUMLOCK,
      eKEY_SCROLLLOCK,
      eKEY_KP7,
      eKEY_KP8,
      eKEY_KP9,
      eKEY_KP4,
      eKEY_KP5,
      eKEY_KP6,
      eKEY_KP1,
      eKEY_KP2,
      eKEY_KP3,
      eKEY_KP0,
      eKEY_ZENKAKUHANKAKU,
      eKEY_RO,
      eKEY_KATAKANA,
      eKEY_HIRAGANA,
      eKEY_HENKAN,
      eKEY_KATAKANAHIRAGANA,
      eKEY_KPJPCOMMA,
      eKEY_KPENTER,
      eKEY_RIGHTCTRL,
      eKEY_KPSLASH,
      eKEY_SYSRQ,
      eKEY_RIGHTALT,
      eKEY_LINEFEED,
      eKEY_HOME,
      eKEY_PAGEUP,
      eKEY_END,
      eKEY_PAGEDOWN,
      eKEY_INSERT,
      eKEY_DELETE,
      eKEY_MACRO,
      eKEY_VOLUMEDOWN,
      eKEY_VOLUMEUP,
      eKEY_KPEQUAL,
      eKEY_KPPLUSMINUS,
      eKEY_KPCOMMA,
      eKEY_HANGUEL,
      eKEY_HANJA,
      eKEY_YEN,
      eKEY_LEFTMETA,
      eKEY_RIGHTMETA,
      eKEY_COMPOSE,
      eKEY_AGAIN,
      eKEY_PROPS,
      eKEY_UNDO,
      eKEY_FRONT,
      eKEY_COPY,
      eKEY_OPEN,
      eKEY_PASTE,
      eKEY_FIND,
      eKEY_CUT,
      eKEY_HELP,
      eKEY_CALC,
      eKEY_SETUP,
      eKEY_WAKEUP,
      eKEY_FILE,
      eKEY_SENDFILE,
      eKEY_DELETEFILE,
      eKEY_XFER,
      eKEY_PROG1,
      eKEY_PROG2,
      eKEY_WWW,
      eKEY_MSDOS,
      eKEY_COFFEE,
      eKEY_DIRECTION,
      eKEY_CYCLEWINDOWS,
      eKEY_MAIL,
      eKEY_BOOKMARKS,
      eKEY_COMPUTER,
      eKEY_CLOSECD,
      eKEY_EJECTCD,
      eKEY_EJECTCLOSECD,
      eKEY_NEXTSONG,
      eKEY_PLAYPAUSE,
      eKEY_PREVIOUSSONG,
      eKEY_STOPCD,
      eKEY_PHONE,
      eKEY_ISO,
      eKEY_CONFIG,
      eKEY_HOMEPAGE,
      eKEY_REFRESH,
      eKEY_MOVE,
      eKEY_EDIT,
      eKEY_SCROLLUP,
      eKEY_SCROLLDOWN,
      eKEY_KPLEFTPAREN,
      eKEY_KPRIGHTPAREN,
      eKEY_F14,
      eKEY_F15,
      eKEY_F16,
      eKEY_F17,
      eKEY_F18,
      eKEY_F19,
      eKEY_F20,
      eKEY_F21,
      eKEY_F22,
      eKEY_F23,
      eKEY_F24,
      eKEY_PLAYCD,
      eKEY_PAUSECD,
      eKEY_PROG3,
      eKEY_PROG4,
      eKEY_SUSPEND,
      eKEY_CLOSE,
      eKEY_BASSBOOST,
      eKEY_PRINT,
      eKEY_HP,
      eKEY_CAMERA,
      eKEY_SOUND,
      eKEY_QUESTION,
      eKEY_EMAIL,
      eKEY_CHAT,
      eKEY_SEARCH,
      eKEY_CONNECT,
      eKEY_FINANCE,
      eKEY_SPORT,
      eKEY_SHOP,
      eKEY_ALTERASE,
      eKEY_CANCEL,
      eKEY_BRIGHTNESSDOWN,
      eKEY_MEDIA,
      eKEY_GOTO,
      eKEY_POWER2,
      eKEY_OPTION,
      eKEY_TIME,
      eKEY_VENDOR,
      eKEY_ARCHIVE,
      eKEY_PROGRAM,
      eKEY_CHANNEL,
      eKEY_FAVORITES,
      eKEY_EPG,
      eKEY_PVR,
      eKEY_MHP,
      eKEY_LANGUAGE,
      eKEY_TITLE,
      eKEY_ANGLE,
      eKEY_ZOOM,
      eKEY_MODE,
      eKEY_KEYBOARD,
      eKEY_SCREEN,
      eKEY_PC,
      eKEY_TV,
      eKEY_TV2,
      eKEY_VCR,
      eKEY_VCR2,
      eKEY_SAT,
      eKEY_SAT2,
      eKEY_CD,
      eKEY_TAPE,
      eKEY_RADIO,
      eKEY_TUNER,
      eKEY_PLAYER,
      eKEY_DVD,
      eKEY_AUX,
      eKEY_MP3,
      eKEY_DIRECTORY,
      eKEY_LIST,
      eKEY_MEMO,
      eKEY_CALENDAR,
      eKEY_CHANNELUP,
      eKEY_CHANNELDOWN,
      eKEY_FIRST,
      eKEY_AB,
      eKEY_NEXT,
      eKEY_RESTART,
      eKEY_SLOW,
      eKEY_SHUFFLE,
      eKEY_BREAK,
      eKEY_PREVIOUS,
      eKEY_DIGITS,
      eKEY_TEEN,
      eKEY_TWEN,
      eKEY_DEL_EOL,
      eKEY_DEL_EOS,
      eKEY_INS_LINE,
      eKEY_DEL_LINE,

      eKEY_USER_1,
      eKEY_USER_2,
      eKEY_USER_3,
      eKEY_USER_4,
      eKEY_USER_5,
      eKEY_USER_6,
      eKEY_USER_7,
      eKEY_USER_8,
      eKEY_USER_9,

      /* Added for X11 */
      eKEY_SUPER_L, /* Windows L */
      eKEY_SUPER_R, /* Windows R */
      eKEY_HASH,
      eKEY_LEFTBRACKET,
      eKEY_RIGHTBRACKET,

      eKEY_LAST_KEY
   };

   KeyEvent() : m_code(eKEY_NONE), m_state(eKEY_STATE_UNKNOWN), m_timestamp(0.0f) {}
   KeyEvent(eKeyCode code, Time t) : m_code(code), m_state(eKEY_STATE_DOWN), m_timestamp(t) {}
   KeyEvent(eKeyCode code, eKeyState state, Time t) : m_code(code), m_state(state), m_timestamp(t) {}

   //! Return the KeyCode of the event
   eKeyCode Code() const { return m_code; }

   //! Return the KeyState of the event
   eKeyState State() const { return m_state; }

   //! Return the timestamp when the press occurred
   Time    GetTimestamp() const { return m_timestamp; }

private:
   eKeyCode  m_code;
   eKeyState m_state;
   Time      m_timestamp;
};

//! A FIFO of KeyEvent elements
class KeyEvents : public Queue<KeyEvent>
{
};

}

#endif /* __BSG_KEY_EVENTS_H__ */

