class Solution:
    def intToRoman(self, num: int) -> str:
        
        out = ""
        
        # Thousands
        while num >= 1000:
            out += "M"
            num -= 1000
        
        # Hundreds
        if num >= 900:
            out += "CM"
            num -= 900
        
        elif num >= 500:
            out += "D"
            num -= 500
        
        elif num >= 400:
            out += "CD"
            num -= 400
        
        while num >= 100:
            out += "C"
            num -= 100
        
        # Tenths
        if num >= 90:
            out += "XC"
            num -= 90
        
        elif num >= 50:
            out += "L"
            num -= 50
        
        elif num >= 40:
            out += "XL"
            num -= 40
        
        while num >= 10:
            out += "X"
            num -= 10
        
        # Units
        if num >= 9:
            out += "IX"
            num -= 9
        
        elif num >= 5:
            out += "V"
            num -= 5
        
        elif num >= 4:
            out += "IV"
            num -= 4
        
        while num >= 1:
            out += "I"
            num -= 1
        
        return out