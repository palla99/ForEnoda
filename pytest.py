import subprocess
import unittest
import time
#revisits
class TestSharedMemoryProgram(unittest.TestCase):

    def run_program(self, message):
        # Run the C program with the given message as an argument
        result = subprocess.run(['./main', message], capture_output=True, text=True)
        return result

    def test_program_output(self):
        print(" Test 1 : Basic test ")
        message = "Simple string"
        result = self.run_program(message)

        # Check if the program ran successfully
        self.assertEqual(result.returncode, 0)

        # Check if the output is as expected
        expected_output = """\
CPU1: Sent 13 bytes
CPU2: Received message: Simple string
CPU2: Received message of 13 bytes
CPU1: Ack received from CPU2 
"""
        self.assertIn(expected_output, result.stdout)
        print(" End Of the Test ")
        time.sleep(1)

    def test_program_with_long_message(self):
        print(" Test 2 : test for 62 bytes ")
        message = "11111111111111111111111111111111111111111111111111111111111111"
        result = self.run_program(message)

        # Check if the program ran successfully
        self.assertEqual(result.returncode, 0)

        # Check if the output is as expected
        #expected_output = f"Received message: {message}\n"
        expected_output = """\
CPU1: Sent 62 bytes
CPU2: Received message: 11111111111111111111111111111111111111111111111111111111111111
CPU2: Received message of 62 bytes
CPU1: Ack received from CPU2 
"""
        self.assertIn(expected_output, result.stdout)
        print(" End Of the Test ")
        time.sleep(1)

    def test_program_with_buffer_over_flow(self):
        print(" Test 3 : testing for Buffer Overflow ")
        message = "11111111111111111111111111111111111111111111111111111111111111111"
        result = self.run_program(message)

        # Check if the program ran successfully
        #self.assertEqual(result.returncode, 0)

        # Check if the output is as expected
        #expected_output = f"Received message: {message}\n"
        expected_output = """\
CPU1: Sent 65 bytes
Buffer Overflow detected 
"""
        self.assertIn(expected_output, result.stdout)
        print(" End Of the Test ")
"""
    def test_program_without_message(self):
        # Run the program without any message
        result = subprocess.run(['./main'], capture_output=True, text=True)

        # Check if the program returned an error
        self.assertNotEqual(result.returncode, 0)

        # Check if the error message is as expected
        #expected_error = "Usage: ./program <message>\n"
        expected_error = "CPU 2 waiting \n"
        self.assertIn(expected_error, result.stderr)"""

if __name__ == '__main__':
    unittest.main()

