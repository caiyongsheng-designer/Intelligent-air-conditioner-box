/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (25)
#endif
/* ISR prototypes */
void sci_uart_rxi_isr(void);
void sci_uart_txi_isr(void);
void sci_uart_tei_isr(void);
void sci_uart_eri_isr(void);
void iic_master_rxi_isr(void);
void iic_master_txi_isr(void);
void gpt_counter_overflow_isr(void);
void iic_master_eri_isr(void);
void adc_scan_end_isr(void);
void rtc_carry_isr(void);
void gpt_capture_a_isr(void);
void gpt_capture_b_isr(void);
void iic_master_tei_isr(void);
void rtc_alarm_periodic_isr(void);
void r_icu_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_SCI1_RXI ((IRQn_Type) 0) /* SCI1 RXI (Received data full) */
#define SCI1_RXI_IRQn          ((IRQn_Type) 0) /* SCI1 RXI (Received data full) */
#define VECTOR_NUMBER_SCI1_TXI ((IRQn_Type) 1) /* SCI1 TXI (Transmit data empty) */
#define SCI1_TXI_IRQn          ((IRQn_Type) 1) /* SCI1 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI1_TEI ((IRQn_Type) 2) /* SCI1 TEI (Transmit end) */
#define SCI1_TEI_IRQn          ((IRQn_Type) 2) /* SCI1 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI1_ERI ((IRQn_Type) 3) /* SCI1 ERI (Receive error) */
#define SCI1_ERI_IRQn          ((IRQn_Type) 3) /* SCI1 ERI (Receive error) */
#define VECTOR_NUMBER_SCI2_RXI ((IRQn_Type) 4) /* SCI2 RXI (Receive data full) */
#define SCI2_RXI_IRQn          ((IRQn_Type) 4) /* SCI2 RXI (Receive data full) */
#define VECTOR_NUMBER_SCI2_TXI ((IRQn_Type) 5) /* SCI2 TXI (Transmit data empty) */
#define SCI2_TXI_IRQn          ((IRQn_Type) 5) /* SCI2 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI2_TEI ((IRQn_Type) 6) /* SCI2 TEI (Transmit end) */
#define SCI2_TEI_IRQn          ((IRQn_Type) 6) /* SCI2 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI2_ERI ((IRQn_Type) 7) /* SCI2 ERI (Receive error) */
#define SCI2_ERI_IRQn          ((IRQn_Type) 7) /* SCI2 ERI (Receive error) */
#define VECTOR_NUMBER_IIC0_RXI ((IRQn_Type) 8) /* IIC0 RXI (Receive data full) */
#define IIC0_RXI_IRQn          ((IRQn_Type) 8) /* IIC0 RXI (Receive data full) */
#define VECTOR_NUMBER_IIC0_TXI ((IRQn_Type) 9) /* IIC0 TXI (Transmit data empty) */
#define IIC0_TXI_IRQn          ((IRQn_Type) 9) /* IIC0 TXI (Transmit data empty) */
#define VECTOR_NUMBER_GPT9_COUNTER_OVERFLOW ((IRQn_Type) 10) /* GPT9 COUNTER OVERFLOW (Overflow) */
#define GPT9_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 10) /* GPT9 COUNTER OVERFLOW (Overflow) */
#define VECTOR_NUMBER_IIC0_ERI ((IRQn_Type) 11) /* IIC0 ERI (Transfer error) */
#define IIC0_ERI_IRQn          ((IRQn_Type) 11) /* IIC0 ERI (Transfer error) */
#define VECTOR_NUMBER_SCI9_RXI ((IRQn_Type) 12) /* SCI9 RXI (Received data full) */
#define SCI9_RXI_IRQn          ((IRQn_Type) 12) /* SCI9 RXI (Received data full) */
#define VECTOR_NUMBER_SCI9_TXI ((IRQn_Type) 13) /* SCI9 TXI (Transmit data empty) */
#define SCI9_TXI_IRQn          ((IRQn_Type) 13) /* SCI9 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI9_TEI ((IRQn_Type) 14) /* SCI9 TEI (Transmit end) */
#define SCI9_TEI_IRQn          ((IRQn_Type) 14) /* SCI9 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI9_ERI ((IRQn_Type) 15) /* SCI9 ERI (Receive error) */
#define SCI9_ERI_IRQn          ((IRQn_Type) 15) /* SCI9 ERI (Receive error) */
#define VECTOR_NUMBER_ADC0_SCAN_END ((IRQn_Type) 16) /* ADC0 SCAN END (A/D scan end interrupt) */
#define ADC0_SCAN_END_IRQn          ((IRQn_Type) 16) /* ADC0 SCAN END (A/D scan end interrupt) */
#define VECTOR_NUMBER_GPT7_COUNTER_OVERFLOW ((IRQn_Type) 18) /* GPT7 COUNTER OVERFLOW (Overflow) */
#define GPT7_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 18) /* GPT7 COUNTER OVERFLOW (Overflow) */
#define VECTOR_NUMBER_RTC_CARRY ((IRQn_Type) 19) /* RTC CARRY (Carry interrupt) */
#define RTC_CARRY_IRQn          ((IRQn_Type) 19) /* RTC CARRY (Carry interrupt) */
#define VECTOR_NUMBER_GPT9_CAPTURE_COMPARE_A ((IRQn_Type) 20) /* GPT9 CAPTURE COMPARE A (Compare match A) */
#define GPT9_CAPTURE_COMPARE_A_IRQn          ((IRQn_Type) 20) /* GPT9 CAPTURE COMPARE A (Compare match A) */
#define VECTOR_NUMBER_GPT9_CAPTURE_COMPARE_B ((IRQn_Type) 21) /* GPT9 CAPTURE COMPARE B (Compare match B) */
#define GPT9_CAPTURE_COMPARE_B_IRQn          ((IRQn_Type) 21) /* GPT9 CAPTURE COMPARE B (Compare match B) */
#define VECTOR_NUMBER_IIC0_TEI ((IRQn_Type) 22) /* IIC0 TEI (Transmit end) */
#define IIC0_TEI_IRQn          ((IRQn_Type) 22) /* IIC0 TEI (Transmit end) */
#define VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW ((IRQn_Type) 24) /* GPT0 COUNTER OVERFLOW (Overflow) */
#define GPT0_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 24) /* GPT0 COUNTER OVERFLOW (Overflow) */
#define VECTOR_NUMBER_RTC_PERIOD ((IRQn_Type) 26) /* RTC PERIOD (Periodic interrupt) */
#define RTC_PERIOD_IRQn          ((IRQn_Type) 26) /* RTC PERIOD (Periodic interrupt) */
#define VECTOR_NUMBER_ICU_IRQ4 ((IRQn_Type) 28) /* ICU IRQ4 (External pin interrupt 4) */
#define ICU_IRQ4_IRQn          ((IRQn_Type) 28) /* ICU IRQ4 (External pin interrupt 4) */
#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
