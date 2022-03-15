clear()
local keyboardIdentifier = '2EEDFCE1'
if keyboardIdentifier == '0000AAA' then
	lmc_assign_keyboard('MACROS');
else lmc_device_set_name('MACROS', keyboardIdentifier);
end
--This lists connected keyboards
dev = lmc_get_devices()
for key,value in pairs(dev) do
  print(key..':')
  for key2,value2 in pairs(value) do print('  '..key2..' = '..value2) end
end

-- ^ = Control
-- % = Alt
-- + = Shift
-- # = Win
-- & = Tab

local config = {
-- Numerics / symbols line
[string.byte('1')] = "{F13}",
[string.byte('2')] = "{F14}",
[string.byte('3')] = "{F15}",
[string.byte('4')] = "{F16}",
[string.byte('5')] = "{F17}",
[string.byte('6')] = "{F18}",
[string.byte('7')] = "{F19}",
[string.byte('8')] = "{F20}",
[string.byte('9')] = "{F21}",
[string.byte('0')] = "{F22}",
[219] = "{F23}", -- °])
[187] = "{F24}", -- +=}
-- 1st characters line
[string.byte('A')] = "^{F13}",
[string.byte('Z')] = "^{F14}",
[string.byte('E')] = "^{F15}",
[string.byte('R')] = "^{F16}",
[string.byte('T')] = "^{F17}",
[string.byte('Y')] = "^{F18}",
[string.byte('U')] = "^{F19}",
[string.byte('I')] = "^{F20}",
[string.byte('O')] = "^{F21}",
[string.byte('P')] = "^{F22}",
[221] = "^{F23}", -- ¨^
[186] = "^{F24}", -- £$¤
-- 2nd characters line
[string.byte('Q')] = "+{F13}",
[string.byte('S')] = "+{F14}",
[string.byte('D')] = "+{F15}",
[string.byte('F')] = "+{F16}",
[string.byte('G')] = "+{F17}",
[string.byte('H')] = "+{F18}",
[string.byte('J')] = "+{F19}",
[string.byte('K')] = "+{F20}",
[string.byte('L')] = "+{F21}",
[string.byte('M')] = "+{F22}",
[192] = "+{F23}", -- %ù
[220] = "+{F24}", -- µ*
-- 3rd characters line
[226] = "%{F13}", -- ><
[string.byte('W')] = "%{F14}",
[string.byte('X')] = "%{F15}",
[string.byte('C')] = "%{F16}",
[string.byte('V')] = "%{F17}",
[string.byte('B')] = "%{F18}",
[string.byte('N')] = "%{F19}",
[188] = "%{F20}", -- ?,
[190] = "%{F21}", -- .;
[191] = "%{F22}", -- /:
[223] = "%{F23}",  -- §!
  -- DO NOT USE SHIFT AS IT CAN STILL BE CATCHED BY SOME SOFTWARES
-- Numeric keypad
[96] =  "^+(F13)", -- 0
[97] =  "^+(F14)", -- 1
[98] =  "^+(F15)", -- 2
[99] =  "^+(F16)", -- 3
[100] =  "^+(F17)", -- 4
[101] =  "^+(F18)", -- 5
[102] =  "^+(F19)", -- 6
[103] =  "^+(F20)", -- 7
[104] =  "^+(F21)", -- 8
[105] =  "^+(F22)", -- 9
}

-- define callback for whole device
lmc_set_handler('MACROS', function(button, direction)
	--Ignoring upstrokes ensures keystrokes are not registered twice, but activates faster than ignoring downstrokes. It also allows press and hold behaviour
        if (direction == 0) then return end -- ignore key upstrokes.
        print('typed: ' .. button)
        if type(config[button]) == "string" then
                                lmc_send_keys(config[button])
	else
                print(' ')
                print('Not yet assigned: ' .. button)
	end
end)
