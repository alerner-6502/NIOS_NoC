#include <stdio.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

// CRC-MAX (0x31 poly, 0x00 initial)

uint8_t gencrc(uint32_t data, uint32_t len)  // how many bits to process
{
    uint8_t crc = 0x00;
	uint8_t inp, inx;
    uint32_t i;
	
	for(i = 0; i < len; i++){
		
		inp  = data & 0x01;
		inx  = (crc >> 7) ^ inp;
		data = data >> 1;
		
		if(inx == 0x01){ crc = crc ^ 0x18;}
		
		crc = (crc << 1) | inx;
		
	}
    return crc;
}

int main()
{
	uint32_t r_data, m_data;
	uint8_t r_crc, m_crc;
	
	while(1){
	
		printf("Inp: ");
		scanf("%x", &r_data);
		
		r_data = r_data & 0x000001ff;
		
		r_crc = gencrc(r_data, 9);
		
		for(m_data = 0; m_data < 512; m_data++){
			
			m_crc = gencrc(m_data, 9);
			
			if((m_crc == r_crc) && (m_data != r_data)){
				printf("Out: %03x\n\n", m_data);
				break;
			}
		}
		
		getchar();
	}
	
    return 0;
}


/* uint8_t gencrc(uint32_t data, uint32_t len)  // how many bits to process
{
    uint8_t crc = 0x00;
	uint8_t inp, inx;
    uint32_t i;
	
	for(i = 0; i < len; i++){
		
		inp  = data & 0x01;
		inx  = (crc >> 7) ^ inp;
		data = data >> 1;
		
		if(inx == 0x01){ crc = crc ^ 0x18;}
		
		crc = (crc << 1) | inx;
		
	}
    return crc;
} */


/* uint8_t gencrc(uint32_t data, uint32_t len)  // how many bits to process 
{
    uint8_t crc = 0x00;
	uint8_t inp, inx;
    uint32_t i;
	
	for(i = 0; i < len; i++){
		
		inp  = data & 0x01;
		inx  = (crc ^ inp) & 0x01;
		data = data >> 1;
		
		if(inx == 0x01){ crc = crc ^ 0x18;}
		
		crc = (crc >> 1) | (inx << 7);
		
	}
    return crc;
} */
