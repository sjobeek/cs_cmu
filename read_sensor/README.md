## CS for Practicing Engineers HW 6


## Required API Funcitonality

 1. Summary data function that tells users what measurements are in the file, the measurement units, the measurement type, how much data has been collected (in bytes), and the time span of the data.

 1. Search by finding the first-occurrence function of a particular data value and when it occurs as well as a next-occurrence function that finds the next occurrence of the data value as well as when it occurs in the data. The function should return the time index of the frame where the data begins.

 1. Read data function that reads and fills buffers of data. Users will provide the start and stop time as well as the measurements of interest. The API will return buffers of data to the user. Note that if there is more data than can be reasonably packed into a single buffer, the API should signal the programmer in some way that there is more data to read.

 1. Support different streams than DataGen (always has time in current format)

# Deliverables 
## API and Design Discussion

### Describe the design of file structure and your rational for the design.

Basic file structure:  line-delimited JSON (see http://jsonlines.org/) with header metadata using a simplified version of the "properties" keyword from JSON Schema (see http://json-schema.org/example1.html)

Benefits:  

 1. Can be appended to or read one line at a time, unlike a single JSON object. Allows for manipulation of large data sets that don't  fit into memory.
 1. Human readable data and metadata.
 1. Self-describing
 1. Supports non-ascii characters natively
 1. Easily extensible without breaking existing code (no dependency on order within each line / data packet)

Downsides:

 1. Summarize function must read entire file.
 1. Lower performance than binary storage format.
 1. Less efficient use of space due to repeated keywords (compression would alleviate)

#### First-line Metadata Example: (MUST be on a single line at top of file)
```JSON
{"Hours": {"type": "integer", "description": "Integer data that represents the data sample time stamp hours."}, "Minutes": {"type": "integer", "description": "Integer data that represents the data sample time stamp minutes"}, "Seconds": {"type": "integer", "description": "Integer data that represents the data sample time stamp seconds."}, "Humidity": {"type": "number", "description": "Floating point data that represents the relative humidity"},"Temperature": {"type": "number", "description": "Floating point data that represents temperature in degrees Fahrenheit."}, "Pressure": {"type": "number", "description": "Floating point data that represents pressure in kilo-Pascals (kPa)."}}
```
#### Data packet examples: (one line per packet) 
```JSON
{"Hours": 13, "Minutes": 12, "Seconds": 22, "Humidity": 12.3, "Temperature": 94.4, "Pressure": 101.3}
{"Hours": 13, "Minutes": 12, "Seconds": 23, "Humidity": 12.2, "Temperature": 94.5, "Pressure": 101.1}
{"Hours": 13, "Minutes": 12, "Seconds": 24, "Humidity": 12.2, "Temperature": 94.2, "Pressure": 100.8}
{"Hours": 13, "Minutes": 12, "Seconds": 25, "Humidity": 12.1, "Temperature": 94.3, "Pressure": 100.6}
```
### Describe how your design meets all of the functions above.

### Provide an analysis of your search algorithms in terms of performance and describe any limitations and tradeoffs you made.
