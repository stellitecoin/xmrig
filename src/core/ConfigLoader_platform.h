/* XTLRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2016-2018 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 * Copyright 2018 XTLRig       <https://github.com/stellitecoin>, <support@stellite.cash>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CONFIGLOADER_PLATFORM_H__
#define __CONFIGLOADER_PLATFORM_H__


#ifdef _MSC_VER
#   include "getopt/getopt.h"
#else
#   include <getopt.h>
#endif


#include "common/interfaces/IConfig.h"
#include "version.h"


namespace xtlrig {


static char const usage[] = "\
Usage: " APP_ID " [OPTIONS]\n\
Options:\n\
  -a, --algo=ALGO          specify the algorithm to use\n\
                             cryptonight\n"
#ifndef XMRIG_NO_AEON
"\
                             cryptonight-lite\n"
#endif
#ifndef XMRIG_NO_SUMO
"\
                             cryptonight-heavy\n"
#endif
"\
  -o, --url=URL            URL of mining server\n\
  -O, --userpass=U:P       username:password pair for mining server\n\
  -u, --user=USERNAME      username for mining server\n\
  -p, --pass=PASSWORD      password for mining server\n\
      --rig-id=ID          rig identifier for pool-side statistics (needs pool support)\n\
  -t, --threads=N          number of miner threads\n\
  -v, --av=N               algorithm variation, 0 auto select\n\
  -k, --keepalive          send keepalived for prevent timeout (need pool support)\n\
  -r, --retries=N          number of times to retry before switch to backup server (default: 5)\n\
  -R, --retry-pause=N      time to pause between retries (default: 5)\n\
      --cpu-affinity       set process affinity to CPU core(s), mask 0x3 for cores 0 and 1\n\
      --cpu-priority       set process priority (0 idle, 2 normal to 5 highest)\n\
      --no-huge-pages      disable huge pages support\n\
      --no-color           disable colored output\n\
      --variant            algorithm PoW variant\n\
      --donate-level=N     donate level, default 5%% (5 minutes in 100 minutes)\n\
      --user-agent         set custom user-agent string for pool\n\
  -B, --background         run the miner in the background\n\
  -c, --config=FILE        load a JSON-format configuration file\n\
  -l, --log-file=FILE      log all output to a file\n"
# ifdef HAVE_SYSLOG_H
"\
  -S, --syslog             use system log for output messages\n"
# endif
"\
      --max-cpu-usage=N    maximum CPU usage for automatic threads mode (default 75)\n\
      --safe               safe adjust threads and av settings for current CPU\n\
      --nicehash           enable nicehash/xtlrig-proxy support\n\
      --print-time=N       print hashrate report every N seconds\n\
      --api-port=N         port for the miner API\n\
      --api-access-token=T access token for API\n\
      --api-worker-id=ID   custom worker-id for API\n\
      --api-ipv6           enable IPv6 support for API\n\
      --api-no-restricted  enable full remote access (only if API token set)\n\
  -h, --help               display this help and exit\n\
  -V, --version            output version information and exit\n\
      --percent            set single cpu max percent\n\
      --simpleSpeed        simple show speed\n\
";


static char const short_options[] = "a:c:khBp:Px:r:R:s:t:T:o:u:O:v:Vl:S";


static struct option const options[] = {
    { "algo",              1, nullptr, xtlrig::IConfig::AlgorithmKey      },
    { "api-access-token",  1, nullptr, xtlrig::IConfig::ApiAccessTokenKey },
    { "api-port",          1, nullptr, xtlrig::IConfig::ApiPort           },
    { "api-worker-id",     1, nullptr, xtlrig::IConfig::ApiWorkerIdKey    },
    { "api-ipv6",          0, nullptr, xtlrig::IConfig::ApiIPv6Key        },
    { "api-no-restricted", 0, nullptr, xtlrig::IConfig::ApiRestrictedKey  },
    { "av",                1, nullptr, xtlrig::IConfig::AVKey             },
    { "background",        0, nullptr, xtlrig::IConfig::BackgroundKey     },
    { "config",            1, nullptr, xtlrig::IConfig::ConfigKey         },
    { "cpu-affinity",      1, nullptr, xtlrig::IConfig::CPUAffinityKey    },
    { "cpu-priority",      1, nullptr, xtlrig::IConfig::CPUPriorityKey    },
    { "donate-level",      1, nullptr, xtlrig::IConfig::DonateLevelKey    },
    { "dry-run",           0, nullptr, xtlrig::IConfig::DryRunKey         },
    { "help",              0, nullptr, xtlrig::IConfig::HelpKey           },
    { "keepalive",         0, nullptr, xtlrig::IConfig::KeepAliveKey      },
    { "log-file",          1, nullptr, xtlrig::IConfig::LogFileKey        },
    { "max-cpu-usage",     1, nullptr, xtlrig::IConfig::MaxCPUUsageKey    },
    { "nicehash",          0, nullptr, xtlrig::IConfig::NicehashKey       },
    { "no-color",          0, nullptr, xtlrig::IConfig::ColorKey          },
    { "no-huge-pages",     0, nullptr, xtlrig::IConfig::HugePagesKey      },
    { "variant",           1, nullptr, xtlrig::IConfig::VariantKey        },
    { "pass",              1, nullptr, xtlrig::IConfig::PasswordKey       },
    { "print-time",        1, nullptr, xtlrig::IConfig::PrintTimeKey      },
    { "retries",           1, nullptr, xtlrig::IConfig::RetriesKey        },
    { "retry-pause",       1, nullptr, xtlrig::IConfig::RetryPauseKey     },
    { "safe",              0, nullptr, xtlrig::IConfig::SafeKey           },
    { "syslog",            0, nullptr, xtlrig::IConfig::SyslogKey         },
    { "threads",           1, nullptr, xtlrig::IConfig::ThreadsKey        },
    { "url",               1, nullptr, xtlrig::IConfig::UrlKey            },
    { "user",              1, nullptr, xtlrig::IConfig::UserKey           },
    { "user-agent",        1, nullptr, xtlrig::IConfig::UserAgentKey      },
    { "userpass",          1, nullptr, xtlrig::IConfig::UserpassKey       },
    { "rig-id",            1, nullptr, xtlrig::IConfig::RigIdKey          },
    { "version",           0, nullptr, xtlrig::IConfig::VersionKey        },
    { "percent",           1, nullptr, xtlrig::IConfig::PercentKey        },
    { "simpleSpeed",       0, nullptr, xtlrig::IConfig::SimpleSpeed       },
    { 0, 0, 0, 0 }
};


static struct option const config_options[] = {
    { "algo",          1, nullptr, xtlrig::IConfig::AlgorithmKey   },
    { "av",            1, nullptr, xtlrig::IConfig::AVKey          },
    { "background",    0, nullptr, xtlrig::IConfig::BackgroundKey  },
    { "colors",        0, nullptr, xtlrig::IConfig::ColorKey       },
    { "cpu-affinity",  1, nullptr, xtlrig::IConfig::CPUAffinityKey },
    { "cpu-priority",  1, nullptr, xtlrig::IConfig::CPUPriorityKey },
    { "donate-level",  1, nullptr, xtlrig::IConfig::DonateLevelKey },
    { "dry-run",       0, nullptr, xtlrig::IConfig::DryRunKey      },
    { "huge-pages",    0, nullptr, xtlrig::IConfig::HugePagesKey   },
    { "log-file",      1, nullptr, xtlrig::IConfig::LogFileKey     },
    { "max-cpu-usage", 1, nullptr, xtlrig::IConfig::MaxCPUUsageKey },
    { "print-time",    1, nullptr, xtlrig::IConfig::PrintTimeKey   },
    { "retries",       1, nullptr, xtlrig::IConfig::RetriesKey     },
    { "retry-pause",   1, nullptr, xtlrig::IConfig::RetryPauseKey  },
    { "safe",          0, nullptr, xtlrig::IConfig::SafeKey        },
    { "syslog",        0, nullptr, xtlrig::IConfig::SyslogKey      },
    { "threads",       1, nullptr, xtlrig::IConfig::ThreadsKey     },
    { "user-agent",    1, nullptr, xtlrig::IConfig::UserAgentKey   },
    { "hw-aes",        0, nullptr, xtlrig::IConfig::HardwareAESKey },
    { "percent",       1, nullptr, xtlrig::IConfig::PercentKey     },
    { "simpleSpeed",   0, nullptr, xtlrig::IConfig::SimpleSpeed    },
    { 0, 0, 0, 0 }
};


static struct option const pool_options[] = {
    { "url",           1, nullptr, xtlrig::IConfig::UrlKey        },
    { "pass",          1, nullptr, xtlrig::IConfig::PasswordKey   },
    { "user",          1, nullptr, xtlrig::IConfig::UserKey       },
    { "userpass",      1, nullptr, xtlrig::IConfig::UserpassKey   },
    { "nicehash",      0, nullptr, xtlrig::IConfig::NicehashKey   },
    { "keepalive",     2, nullptr, xtlrig::IConfig::KeepAliveKey  },
    { "variant",       1, nullptr, xtlrig::IConfig::VariantKey    },
    { "rig-id",        1, nullptr, xtlrig::IConfig::RigIdKey      },
    { 0, 0, 0, 0 }
};


static struct option const api_options[] = {
    { "port",          1, nullptr, xtlrig::IConfig::ApiPort           },
    { "access-token",  1, nullptr, xtlrig::IConfig::ApiAccessTokenKey },
    { "worker-id",     1, nullptr, xtlrig::IConfig::ApiWorkerIdKey    },
    { "ipv6",          0, nullptr, xtlrig::IConfig::ApiIPv6Key        },
    { "restricted",    0, nullptr, xtlrig::IConfig::ApiRestrictedKey  },
    { 0, 0, 0, 0 }
};


} /* namespace xtlrig */

#endif /* __CONFIGLOADER_PLATFORM_H__ */
