using System;
using System.Text;
using System.Runtime.InteropServices;
using System.Globalization;

class Program
{
    // Path to the DLL library
    private const string DLL_PATH = @"ups-control.dll";

    // Import the function to initialize the library
    [DllImport(DLL_PATH, CallingConvention = CallingConvention.Cdecl, EntryPoint = "initialize")]
    private static extern IntPtr InitializeLibrary();

    // Import the function to open a USB device
    [DllImport(DLL_PATH, CallingConvention = CallingConvention.Cdecl, EntryPoint = "open_device")]
    private static extern IntPtr OpenDevice(IntPtr context, int vendorId, int productId);

    // Import the function to close a USB device
    [DllImport(DLL_PATH, CallingConvention = CallingConvention.Cdecl, EntryPoint = "close_device")]
    private static extern void CloseDevice(IntPtr deviceHandle, IntPtr context);

    // Import the function to get the UPS name
    [DllImport(DLL_PATH, CallingConvention = CallingConvention.Cdecl, EntryPoint = "get_ups_name")]
    private static extern int GetUpsName(IntPtr deviceHandle);

    // Import the function to get the UPS status
    [DllImport(DLL_PATH, CallingConvention = CallingConvention.Cdecl, EntryPoint = "get_ups_status")]
    private static extern int GetUpsStatus(IntPtr deviceHandle);

    // Import the function to test the UPS with a standard duration (10 seconds)
    [DllImport(DLL_PATH, CallingConvention = CallingConvention.Cdecl, EntryPoint = "test_ups")]
    private static extern int TestUps(IntPtr deviceHandle);

    // Import the function to get the last response from the UPS
    [DllImport(DLL_PATH, CharSet = CharSet.Ansi, EntryPoint = "get_last_response")]
    private static extern IntPtr GetLastResponse();

    static void Main()
    {
        // Initialize the library
        IntPtr context = InitializeLibrary();
        if (context == IntPtr.Zero)
        {
            Console.WriteLine("Failed to initialize the library.");
            return;
        }
        Console.WriteLine($"Library initialized successfully with context at 0x{context:X}");

        // Set USB device identifiers
        const int VendorId = 0x0001;
        const int ProductId = 0x0000;

        // Open the USB device
        IntPtr deviceHandle = OpenDevice(context, VendorId, ProductId);
        if (deviceHandle == IntPtr.Zero)
        {
            Console.WriteLine("Failed to open the USB device.");
            CloseDevice(deviceHandle, context);
            return;
        }
        Console.WriteLine($"Device handle opened successfully at 0x{deviceHandle:X}");

        // Get UPS name
        int result = GetUpsName(deviceHandle);
        if (result == -1)
        {
            Console.WriteLine("Failed to get the UPS name.");
        }
        else if (result == 0)
        {
            // Retrieve the last response from the UPS
            IntPtr namePtr = GetLastResponse();
            string upsName = Marshal.PtrToStringAnsi(namePtr);
            Console.WriteLine($"UPS Name: {upsName}");
        }

        // Get UPS status
        result = GetUpsStatus(deviceHandle);
        if (result == -1)
        {
            Console.WriteLine("Failed to get the UPS status.");
        }
        else if (result == 0)
        {
            // Retrieve the last response from the UPS
            IntPtr statusPtr = GetLastResponse();
            string statusResponse = Marshal.PtrToStringAnsi(statusPtr);

            // Split the status response into individual values
            string[] statusValues = statusResponse.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

            // Parse and display UPS status values
            if (statusValues.Length >= 7)
            {
                double inputVoltage = double.Parse(statusValues[0], CultureInfo.InvariantCulture);
                double inputFaultVoltage = double.Parse(statusValues[1], CultureInfo.InvariantCulture);
                double outputVoltage = double.Parse(statusValues[2], CultureInfo.InvariantCulture);
                double outputCurrent = double.Parse(statusValues[3], CultureInfo.InvariantCulture);
                double inputFrequency = double.Parse(statusValues[4], CultureInfo.InvariantCulture);
                double batteryVoltage = double.Parse(statusValues[5], CultureInfo.InvariantCulture);
                double temperature = double.Parse(statusValues[6], CultureInfo.InvariantCulture);

                // Display UPS status
                Console.WriteLine($"Input Voltage: {inputVoltage} V");
                Console.WriteLine($"Input Fault Voltage: {inputFaultVoltage} V");
                Console.WriteLine($"Output Voltage: {outputVoltage} V");
                Console.WriteLine($"Output Current: {outputCurrent}%");
                Console.WriteLine($"Input Frequency: {inputFrequency} Hz");
                Console.WriteLine($"Battery Voltage: {batteryVoltage} V");
                Console.WriteLine($"Temperature: {temperature} °C");
            }
            else
            {
                Console.WriteLine("Unexpected status response format.");
            }
        }

        // Test the UPS
        TestUps(deviceHandle);

        // Close the device and exit
        CloseDevice(deviceHandle, context);
    }
}