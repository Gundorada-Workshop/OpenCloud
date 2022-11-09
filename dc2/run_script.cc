#include "common/log.h"
#include "run_script.h"

set_log_channel("run_script");

// 001873C0
void CRunScript::exe(vmcode_t* code)
{
  m_vmcode = code;

  for (;; m_vmcode += 1)
  {
    switch (m_vmcode->instruction)
    {
      case 1:
        // 00187414
        todo;
        break;
      case 2:
        // 001876A0
        todo;
        break;
      case 3:
        // 001878E8
        todo;
        break;
      case 4:
        // 00187958
        todo;
        break;
      case 5:
        // 00187890
        todo;
        break;
      case 6:
        // 00187D00
        todo;
        break;
      case 7:
        // 00187E30
        todo;
        break;
      case 8:
        // 00187F60
        todo;
        break;
      case 9:
        // 00188090
        todo;
        break;
      case 10:
        // 00188208
        todo;
        break;
      case 11:
        // 00188300
        todo;
        break;
      case 12:
        // 00188550
        todo;
        break;
      case 13:
        // 001885E0
        todo;
        break;
      case 14:
        // 00187A38
        todo;
        break;
      case 15:
        // 0018871C
        todo;
        break;
      case 16:
        // 00187968
        todo;
        break;
      case 17:
        // 001879E0
        todo;
        break;
      case 18:
        // 00187988
        todo;
        break;
      case 19:
        // 001886F0
        todo;
        break;
      case 20:
        // 00188670
        todo;
        break;
      case 21:
        // 0018869C
        todo;
        break;
      case 23:
        // 001887A8
        todo;
        break;
      case 24:
        // 00188270
        todo;
        break;
      case 25:
        // 001882B8
        todo;
        break;
      case 26:
        // 001884D8
        todo;
        break;
      case 27:
        // 001886DC
        todo;
        break;
      case 28:
        // 001887BC
        todo;
        break;
      case 29:
        // 00188398
        todo;
        break;
      case 30:
        // 00188438
        todo;
        break;
      case 0:
      case 22:
      default:
        // 00187C08
        // nop
        break;
    }
  }
}