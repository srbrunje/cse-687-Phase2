#pragma once

class LogLevel {
	public:
		enum _logLevel {
			Pass_Fail = 1,
			Pass_Fail_with_error_message = 2,
			Pass_Fail_with_test_duration = 3,
			Pass_Fail_with_error_message_and_test_duration = 4
		};

		virtual ~LogLevel() = 0; // makes the class abstract

		// LogLevel::_logLevel l // _logLevel is declared as the enum
		// l = _logLevel::Pass_Fail assigns the enum value
};
