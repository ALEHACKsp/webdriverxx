#ifndef WEBDRIVERXX_BROWSERS_FIREFOX_H
#define WEBDRIVERXX_BROWSERS_FIREFOX_H

#include "../capabilities.h"
#include <cstdlib>

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#include <filesystem>
#else
// TODO: https://github.com/gulrak/filesystem as submodule
#endif

namespace webdriverxx {

// TODO: this is dont written
class FirefoxBinary {
public:
	FirefoxBinary(const Session& driver, const std::string& path = "", const std::string& logfile = "") {
		startcmd_ = path;
		if (!logfile.empty()) {
			logfile_.open(logfile, std::ofstream::binary);
		} else {
			logfile_.open("/dev/null", std::ofstream::binary);
			//std::streambuf* strm_buffer = std::cout.rdbuf();
			//std::cout.rdbuf(file.rdbuf());
		}
		commandline_.clear();
		platform_ = driver.GetCapabilities().GetPlatform();
		if (startcmd_.empty())
			startcmd_ = GetFirefoxStartCmd();
		if (split(startcmd_).size() < 1) {
			WebDriverException("\
Failed to find firefox binary. You can set it by specifying the path to 'firefox_binary':\n\n\
#include \"webdriverxx/browsers/firefox.h\"\n\n\
FirefoxBinary binary = FirefoxBinary(driver, \"/path/to/binary\");\n\
auto ff = Start(Firefox(binary=binary));\n\
			"); // BUG: WTF
		}
	}

	std::string GetFirefoxStartCmd() const {
		std::string startcmd = "";
		if (platform_ == "darwin") {
			startcmd = "/Applications/Firefox.app/Contents/MacOS/firefox-bin";
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
			if (!std::filesystem::exists(startcmd)) {

			}
#else
// TODO: Goto on line 10
#endif

#ifdef WIN32_
			startcmd = std::getenv("USERPROFILE") + startcmd;
#else
			/*
			>>> os.path.expanduser(~/file.txt)
			# '/home/docs/file.txt'

			>>> os.environ["HOME"] = '/home/testuser'
			>>> os.path.expanduser(~/file.txt)
			# '/home/testuser/file.txt'

			>>> os.path.expanduser('~docs/file.txt')
			# '/home/docs/file.txt'
			*/
#endif

		} else if (platform_ == "windows") {

		} else if (platform_ == "java") {

		} else {

		}
	}
private:
	std::string startcmd_;
	std::ofstream logfile_;
	std::string commandline_;
	std::string platform_;
	std::string enviroment_;
};

struct FirefoxOptions : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(FirefoxOptions)
	//WEBDRIVERXX_PROPERTY(FirefoxBinary,         "binary",                    FirefoxBinary)
	WEBDRIVERXX_PROPERTY(FirefoxPreferences,    "prefs",                     std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(FirefoxProfile,        "profile",                   std::string)
	WEBDRIVERXX_PROPERTY(FirefoxProxy,          "proxy",                     Proxy)
	WEBDRIVERXX_PROPERTY(FirefoxLogFile,        "log",                       std::string)
	//WEBDRIVERXX_PROPERTY(FirefoxProfile,      "firefox_profile",           std::string)
	WEBDRIVERXX_PROPERTY(LoggingPrefs,          "loggingPrefs",              LoggingPrefs)
	//WEBDRIVERXX_PROPERTY(FirefoxBinary,       "firefox_binary",			 std::string)
	WEBDRIVERXX_PROPERTY(PageLoadingStrategy,   "pageLoadingStrategy",		 std::string)
	// Tested section
	WEBDRIVERXX_PROPERTY(FirefoxArgs,           "args",						 std::vector<std::string>)
	WEBDRIVERXX_PROPERTIES_END()
};
	
// FIXME: Deprecated FirefoxProfile
struct FirefoxProfile : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(FirefoxProfile)
	WEBDRIVERXX_PROPERTY(AcceptUntrustedCerts,  "webdriver_accept_untrusted_certs",  bool)
	WEBDRIVERXX_PROPERTY(AssumeUntrustedIssuer, "webdriver_assume_untrusted_issuer", bool)
	WEBDRIVERXX_PROPERTY(LogDriver,             "webdriver.log.driver",              log_level::Value)
	WEBDRIVERXX_PROPERTY(FirefoxLogFile,        "webdriver.log.file",                std::string)
	WEBDRIVERXX_PROPERTY(LoadStrategy,          "webdriver.load.strategy",           std::string)
	WEBDRIVERXX_PROPERTY(Port,               "webdriver_firefox_port",            int) // default 7055
	WEBDRIVERXX_PROPERTIES_END()
};

struct Firefox : Capabilities { // copyable
	Firefox(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
		SetBrowserName(browser::Firefox);
		SetVersion("");
		SetPlatform(platform::Any);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(Firefox)
	WEBDRIVERXX_PROPERTY(FirefoxOptions,      "moz:firefoxOptions",     FirefoxOptions)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
