#pragma once

namespace Rosefinch
{
	namespace RHI
	{
        enum class ValidationMode
        {
            Disabled,
            // Print warnings and errors
            Enabled,
            // Print all warnings, errors and info messages
            Verbose,
            // Enable GPU-based validation
            GPU
        };

        // Read the RHI validation mode considering configurations,
        // cvars, command line options and registry settings.
        ValidationMode ReadValidationMode();
	}
}