#pragma once
#include<string>

namespace Instrumentation {
  namespace FocusPX
  {
    constexpr wchar_t  PA_PORT[] = L"PA";
    constexpr wchar_t  UT_P1_PORT[] = L"P1";
    constexpr wchar_t  UT_P2_PORT[] = L"P2";
    constexpr wchar_t  UT_P3_PORT[] = L"P3";
    constexpr wchar_t  UT_P4_PORT[] = L"P4";
    constexpr wchar_t  UT_P1R1_PORT[] = L"P1/R1";
    constexpr wchar_t  UT_P2R2_PORT[] = L"P2/R2";
    constexpr wchar_t  UT_P3R3_PORT[] = L"P3/R3";
    constexpr wchar_t  UT_P4R4_PORT[] = L"P4/R4";

    constexpr wchar_t  GPIO_IO_PORT[] = L"I/O LEMO";
    constexpr wchar_t  GPIO_DIG_OUT_ALARMS_PORT[] = L"DIG. OUT ALARMS";
    
    enum class UT_Port { PA, P1, P2, P3, P4, P1R1, P2R2, P3R3, P4R4 };
    enum class GPIO_Port { IO, DIGOUTALARMS };
    enum class DIN_Pin { DIN1, DIN2, DIN3, DIN4, DOUT1, DOUT2, DOUT3 };
    enum class DOUT_Pin { DIGOUT1, DIGOUT2, DIGOUT3, DIGOUT4, ALARMOUT1, ALARMOUT2, ALARMOUT3, ALARMOUT4 };
    enum class Encoder_Pin { PHA_AX1, PHB_AX1, PHB_AX2, PHA_AX2 };
  }

  namespace OmniScanX3
  {
    constexpr wchar_t  PA_PORT[] = L"PA";
    constexpr wchar_t  UT_P1_PORT[] = L"P1";
    constexpr wchar_t  UT_R1_PORT[] = L"R1";
    constexpr wchar_t  UT_P2_PORT[] = L"P2";
    constexpr wchar_t  UT_R2_PORT[] = L"R2";

    constexpr wchar_t  GPIO_IO_PORT[] = L"I/O LEMO";
    constexpr wchar_t  GPIO_DIG_OUT_ALARMS_PORT[] = L"DIG. OUT ALARMS";

    enum class UT_Port { PA, P1, R1, P2, R2};
    enum class GPIO_Port { IO, DIGOUTALARMS };
    enum class DIN_Pin { DIN1, DIN2, DIN3, DIN4, DOUT1, DOUT2, DOUT3 };
    enum class DOUT_Pin { DIGOUT1, DIGOUT2, DIGOUT3, DIGOUT4, ALARMOUT1, ALARMOUT2, ALARMOUT3, ALARMOUT4 };
    enum class Encoder_Pin { PHA_AX1, PHB_AX1, PHB_AX2, PHA_AX2 };
  }

  namespace OmniScanMX2
  {
    constexpr wchar_t  PA_PORT[] = L"PA";
    constexpr wchar_t  UT_P1_PORT[] = L"P1";
    constexpr wchar_t  UT_R1_PORT[] = L"R1";
    constexpr wchar_t  UT_P2_PORT[] = L"P2";
    constexpr wchar_t  UT_R2_PORT[] = L"R2";

    constexpr wchar_t  GPIO_IO_PORT[] = L"I/O LEMO";
    constexpr wchar_t  GPIO_DIG_OUT_ALARMS_PORT[] = L"DIG. OUT ALARMS";

    enum class UT_Port { PA, P1, R1, P2, R2 };
    enum class GPIO_Port { IO, DIGOUTALARMS };
    enum class DIN_Pin { DIN1, DIN2, DIN3, DIN4, DOUT1, DOUT2, DOUT3 };
    enum class DOUT_Pin { DIGOUT1, DIGOUT2, DIGOUT3, DIGOUT4, ALARMOUT1, ALARMOUT2, ALARMOUT3, ALARMOUT4 };
    enum class Encoder_Pin { PHA_AX1, PHB_AX1, PHB_AX2, PHA_AX2 };
  }
  
  class DevicePort
  {
  public:
    static int ToIndex(FocusPX::UT_Port port)
    {
      switch (port)
      {
      case FocusPX::UT_Port::PA:
        return 0;
      case FocusPX::UT_Port::P1:
        return 0;
      case FocusPX::UT_Port::P2:
        return 1;
      case FocusPX::UT_Port::P3:
        return 2;
      case FocusPX::UT_Port::P4:
        return 3;
      case FocusPX::UT_Port::P1R1:
        return 4;
      case FocusPX::UT_Port::P2R2:
        return 5;
      case FocusPX::UT_Port::P3R3:
        return 6;
      case FocusPX::UT_Port::P4R4:
        return 7;
      default:
        throw std::invalid_argument("No index matches the given UT port.");
      }
    };

    static int ToIndex(FocusPX::GPIO_Port port)
    {
      switch (port)
      {
      case FocusPX::GPIO_Port::IO:
        return 0;
      case FocusPX::GPIO_Port::DIGOUTALARMS:
        return 1;
      default:
        throw std::invalid_argument("No index matches the given GPIO port.");

      }
    };

    static int ToIndex(FocusPX::DIN_Pin pin)
    {
      switch (pin)
      {
      case FocusPX::DIN_Pin::DIN1:
        return 0;
      case FocusPX::DIN_Pin::DIN2:
        return 1;
      case FocusPX::DIN_Pin::DIN3:
        return 2;
      case FocusPX::DIN_Pin::DIN4:
        return 3;
      case FocusPX::DIN_Pin::DOUT1:
        return 4;
      case FocusPX::DIN_Pin::DOUT2:
        return 5;
      case FocusPX::DIN_Pin::DOUT3:
        return 6;
      default:
        throw std::invalid_argument("No index matches the given digital input pin.");
      }
    };

    static int ToIndex(FocusPX::DOUT_Pin pin)
    {
      switch (pin)
      {
      case FocusPX::DOUT_Pin::DIGOUT1:
        return 0;
      case FocusPX::DOUT_Pin::DIGOUT2:
        return 1;
      case FocusPX::DOUT_Pin::DIGOUT3:
        return 2;
      case FocusPX::DOUT_Pin::DIGOUT4:
        return 3;
      case FocusPX::DOUT_Pin::ALARMOUT1:
        return 4;
      case FocusPX::DOUT_Pin::ALARMOUT2:
        return 5;
      case FocusPX::DOUT_Pin::ALARMOUT3:
        return 6;
      case FocusPX::DOUT_Pin::ALARMOUT4:
        return 7;
      default:
        throw std::invalid_argument("No index matches the given digital output pin.");
      }
    };

    static int ToId(FocusPX::DIN_Pin pin)
    {
      switch (pin)
      {
      case FocusPX::DIN_Pin::DIN1:
        return 3;
      case FocusPX::DIN_Pin::DIN2:
        return 4;
      case FocusPX::DIN_Pin::DIN3:
        return 5;
      case FocusPX::DIN_Pin::DIN4:
        return 6;
      case FocusPX::DIN_Pin::DOUT1:
        return 7;
      case FocusPX::DIN_Pin::DOUT2:
        return 8;
      case FocusPX::DIN_Pin::DOUT3:
        return 13;
      default:
        throw std::invalid_argument("No index matches the given digital input pin.");
      }
    };

    static int ToId(FocusPX::DOUT_Pin pin)
    {
      switch (pin)
      {
      case FocusPX::DOUT_Pin::DIGOUT1:
        return 2;
      case FocusPX::DOUT_Pin::DIGOUT2:
        return 3;
      case FocusPX::DOUT_Pin::DIGOUT3:
        return 4;
      case FocusPX::DOUT_Pin::DIGOUT4:
        return 5;
      case FocusPX::DOUT_Pin::ALARMOUT1:
        return 7;
      case FocusPX::DOUT_Pin::ALARMOUT2:
        return 8;
      case FocusPX::DOUT_Pin::ALARMOUT3:
        return 9;
      case FocusPX::DOUT_Pin::ALARMOUT4:
        return 10;
      default:
        throw std::invalid_argument("No index matches the given digital output pin.");
      }
    };

    static int ToId(FocusPX::Encoder_Pin pin)
    {
      switch (pin)
      {
      case FocusPX::Encoder_Pin::PHA_AX1:
        return 9;
      case FocusPX::Encoder_Pin::PHB_AX1:
        return 10;
      case FocusPX::Encoder_Pin::PHB_AX2:
        return 11;
      case FocusPX::Encoder_Pin::PHA_AX2:
        return 12;
      default:
        throw std::invalid_argument("No index matches the given encoder pin.");
      }
    };

    static std::wstring ToString(FocusPX::UT_Port port)
    {
      switch (port)
      {
      case FocusPX::UT_Port::PA:
        return FocusPX::PA_PORT;
      case FocusPX::UT_Port::P1:
        return FocusPX::UT_P1_PORT;
      case FocusPX::UT_Port::P2:
        return FocusPX::UT_P2_PORT;
      case FocusPX::UT_Port::P3:
        return FocusPX::UT_P3_PORT;
      case FocusPX::UT_Port::P4:
        return FocusPX::UT_P4_PORT;
      case FocusPX::UT_Port::P1R1:
        return FocusPX::UT_P1R1_PORT;
      case FocusPX::UT_Port::P2R2:
        return FocusPX::UT_P2R2_PORT;
      case FocusPX::UT_Port::P3R3:
        return FocusPX::UT_P3R3_PORT;
      case FocusPX::UT_Port::P4R4:
        return FocusPX::UT_P4R4_PORT;
      default:
        throw std::invalid_argument("No string matches the given UT port.");
      }
    };

    static std::wstring ToString(FocusPX::GPIO_Port port)
    {
      switch (port)
      {
      case FocusPX::GPIO_Port::IO:
        return FocusPX::GPIO_IO_PORT;
      case FocusPX::GPIO_Port::DIGOUTALARMS:
        return FocusPX::GPIO_DIG_OUT_ALARMS_PORT;
      default:
        throw std::invalid_argument("No string matches the given GPIO port.");
      }
    };


    static int ToIndex(OmniScanX3::UT_Port port)
    {
      switch (port)
      {
      case OmniScanX3::UT_Port::PA:
        return 0;
      case OmniScanX3::UT_Port::P1:
        return 0;
      case OmniScanX3::UT_Port::P2:
        return 1;
      case OmniScanX3::UT_Port::R1: // P1R1
        return 2;
      case OmniScanX3::UT_Port::R2: // P2R2
        return 3;
      default:
        throw std::invalid_argument("No index matches the given UT port.");
      }
    };

    static int ToIndex(OmniScanX3::GPIO_Port port)
    {
      switch (port)
      {
      case OmniScanX3::GPIO_Port::IO:
        return 0;
      case OmniScanX3::GPIO_Port::DIGOUTALARMS:
        return 1;
      default:
        throw std::invalid_argument("No index matches the given GPIO port.");

      }
    };

    static int ToId(OmniScanX3::DIN_Pin pin)
    {
      switch (pin)
      {
      case OmniScanX3::DIN_Pin::DIN1:
        return 3;
      case OmniScanX3::DIN_Pin::DIN2:
        return 4;
      case OmniScanX3::DIN_Pin::DIN3:
        return 5;
      case OmniScanX3::DIN_Pin::DIN4:
        return 6;
      case OmniScanX3::DIN_Pin::DOUT1:
        return 7;
      case OmniScanX3::DIN_Pin::DOUT2:
        return 8;
      case OmniScanX3::DIN_Pin::DOUT3:
        return 13;
      default:
        throw std::invalid_argument("No index matches the given digital input pin.");
      }
    };

    static int ToId(OmniScanX3::DOUT_Pin pin)
    {
      switch (pin)
      {
      case OmniScanX3::DOUT_Pin::DIGOUT1:
        return 2;
      case OmniScanX3::DOUT_Pin::DIGOUT2:
        return 3;
      case OmniScanX3::DOUT_Pin::DIGOUT3:
        return 4;
      case OmniScanX3::DOUT_Pin::DIGOUT4:
        return 5;
      case OmniScanX3::DOUT_Pin::ALARMOUT1:
        return 7;
      case OmniScanX3::DOUT_Pin::ALARMOUT2:
        return 8;
      case OmniScanX3::DOUT_Pin::ALARMOUT3:
        return 9;
      case OmniScanX3::DOUT_Pin::ALARMOUT4:
        return 10;
      default:
        throw std::invalid_argument("No index matches the given digital output pin.");
      }
    };

    static int ToId(OmniScanX3::Encoder_Pin pin)
    {
      switch (pin)
      {
      case OmniScanX3::Encoder_Pin::PHA_AX1:
        return 9;
      case OmniScanX3::Encoder_Pin::PHB_AX1:
        return 10;
      case OmniScanX3::Encoder_Pin::PHB_AX2:
        return 11;
      case OmniScanX3::Encoder_Pin::PHA_AX2:
        return 12;
      default:
        throw std::invalid_argument("No index matches the given encoder pin.");
      }
    };

    static std::wstring ToString(OmniScanX3::UT_Port port)
    {
      switch (port)
      {
      case OmniScanX3::UT_Port::PA:
        return OmniScanX3::PA_PORT;
      case OmniScanX3::UT_Port::P1:
        return OmniScanX3::UT_P1_PORT;
      case OmniScanX3::UT_Port::P2:
        return OmniScanX3::UT_P2_PORT;
      case OmniScanX3::UT_Port::R1:
        return OmniScanX3::UT_R1_PORT;
      case OmniScanX3::UT_Port::R2:
        return OmniScanX3::UT_R2_PORT;
      default:
        throw std::invalid_argument("No string matches the given UT port.");
      }
    };

    static std::wstring ToString(OmniScanX3::GPIO_Port port)
    {
      switch (port)
      {
      case OmniScanX3::GPIO_Port::IO:
        return OmniScanX3::GPIO_IO_PORT;
      case OmniScanX3::GPIO_Port::DIGOUTALARMS:
        return OmniScanX3::GPIO_DIG_OUT_ALARMS_PORT;
      default:
        throw std::invalid_argument("No string matches the given GPIO port.");
      }
    };

  };
}
