# About modding

## Add new menus

You may want to change the menus displayed by the game, or add your own. Luckily, Racedriver has be developed with modding in mind, so you can create your own menus, with all the elements described in the next chapter.
The menus are defined in "./Data/Menus/" folder, inside XML files with a specific syntax and allowed tags & attributes.
The menu component will attempt to run menu with "Home" Id inside "./Data/Menus/Main.xml" file when game starts. If it fails to find it, game will exit.

## Menu elements

<table>
  <tr>
    <th>Tag</th>
    <th>Attribute</th>
    <th>Description</th>
  </tr>
  <!-- Generic -->
  <tr>
    <td rowspan="2">All</td>
    <td colspan="2">Every element implements these methods</td>
  </tr>
  <tr>
    <td>Id</td>
    <td>Sets id of element for interaction in script</td>
  </tr>
  <!-- Text -->
  <tr>
    <td rowspan="1">Menu</td>
    <td colspan="2">Container for menu items</td>
  </tr>
  <!-- Text -->
  <tr>
    <td rowspan="1">Text</td>
    <td colspan="2">Non selectable entry of characters</td>
  </tr>
  <!-- Lang -->
  <tr>
    <td rowspan="1">Lang</td>
    <td colspan="2">Load lang unit with same Id from locale file</td>
  </tr>
  <!-- Sep -->
  <tr>
    <td>Sep</td>
    <td colspan="2">Non selectable horizontal separator</td>
  </tr>
  <!-- Button -->
  <tr>
    <td rowspan="4">Button</td>
    <td colspan="2">Clickable entry</td>
  </tr>
  <tr>
    <td>Type</td>
    <td>Can be any of: { Intern, Goto, Script }</td>
  </tr>
  <tr>
    <td>Target</td>
    <td>Source, function or scriptId to execute</td>
  </tr>
  <tr>
    <td>Path</td>
    <td>Path where the source is located if extern</td>
  </tr>
  <!-- Input -->
  <tr>
    <td rowspan="2">Input</td>
    <td colspan="2">Field to input characters</td>
  </tr>
  <!-- Select -->
  <tr>
    <td rowspan="2">Select</td>
    <td colspan="2">multi-value selection item</td>
  </tr>
  <!-- Option -->
  <tr>
    <td rowspan="2">Option</td>
    <td colspan="2">selectable item from select</td>
  </tr>
  <tr>
    <td>Value</td>
    <td>Sets value corresponding to text</td>
  </tr>
  <!-- Script -->
  <tr>
    <td rowspan="2">Script</td>
    <td colspan="2">Lua embedded script called by Id, or position in menu</td>
  </tr>
  <!-- Alert -->
  <tr>
    <td rowspan="2">Alert</td>
    <td colspan="2">Menu embedded alert message</td>
  </tr>
</table>

## Menu example

This is an example of a basic menu written in racedriver markup:

    <Menu Id="ExampleMenu">
      <Text>Example label</Text>
      <Sep/>
      <Button Type='Intern' Target='alert("amazing")'>Print!</Button>
    </Menu>

This is an advanced menu example :

    <Menu Id="NewGame">
      <Text>Game Creation Menu</Text>
      <Select Text="Select difficulty">
        <Option Value="0"><Lang Id="difficulty.easy"/></Option>
        <Option Value="1"><Lang Id="difficulty.medium"/></Option>
      </Select>
      <Select Id="Locale" Text="Locale">
        <Option Value="en-US">en-US</Option>
        <Option Value="fr-FR">fr-FR</Option>
      </Select>
      <Input Id="Profile"><Lang Id="global.name"/></Input>
      <Button Type="Intern" Target='alert("ok")'>Create Profile</Button>
      <Button Type="Goto" Target="Home">Back</Button>
    </Menu>

## Script Engine (lua)

You may want to have custom behaviour inside your menus, racedriver implement its own script engine. The language of the script is lua, which allow very simple learning for easy customization, and exposes C++ Data easily (C++ binding is explained in next chapter)

## Script C++ Binding

If you need access to C++ Parts, the following are implemented in lua:

<table>
  <tr>
    <th>Object</th>
    <th>Method/Member</th>
    <th>Description</th>
  </tr>
  <!-- Generic -->
  <tr>
    <td rowspan="5">Any Part</td>
    <td colspan="2">Base class of any parts (Car included)</td>
  </tr>
  <tr>
    <td>name</td>
    <td>string name of part</td>
  </tr>
  <tr>
    <td>manufacturer</td>
    <td>string name of manufacturer of part</td>
  </tr>
  <tr>
    <td>socket</td>
    <td>string compatibility socket of part</td>
  </tr>
  <tr>
    <td>price</td>
    <td>int price of part</td>
  </tr>
  <!-- Car -->
  <tr>
    <td rowspan="1">Car</td>
    <td colspan="2">Vehicle (Part)</td>
  </tr>
  <!-- Engine -->
  <tr>
    <td rowspan="3">Engine</td>
    <td colspan="2">Vehicle engine (Part)</td>
  </tr>
  <tr>
    <td>getPower()</td>
    <td>returns string containing max power in ch at max rpm</td>
  </tr>
  <tr>
    <td>getRevolutions()</td>
    <td>returns string containing enigne optimal rpm</td>
  </tr>
  <!-- Spoiler -->
  <tr>
    <td rowspan="2">Spoiler</td>
    <td colspan="2">Vehicle spoiler (Part)</td>
  </tr>
  <tr>
    <td>getAerodynamic()</td>
    <td>returns string containing part aerodynamic percent</td>
  </tr>
  <!-- Tires -->
  <tr>
    <td rowspan="1">Tires</td>
    <td colspan="2">Vehicle tires (Part)</td>
  </tr>
</table>

If you need access to C++ Collections and Data, the following are implemented in lua:

<table>
  <tr>
    <th>Object</th>
    <th>Method/Member</th>
    <th>Description</th>
  </tr>
  <!-- Generic -->
  <tr>
    <td rowspan="5">Collection</td>
    <td colspan="2">Acts as a container of Parts</td>
  </tr>
  <tr>
    <td>size</td>
    <td>returns int size of collection</td>
  </tr>
  <tr>
    <td>operator[idx]</td>
    <td>return reference to part at given int index (idx)</td>
  </tr>
  <tr>
    <td>at(id)</td>
    <td>return reference to part with string Id (id)</td>
  </tr>
  <tr>
    <td>filterCompatible(car)</td>
    <td>return a new collection of parts with same socket as given Car (car)</td>
  </tr>
  <!-- Car -->
  <tr>
    <td rowspan="1">Cars</td>
    <td colspan="2">Cars collection</td>
  </tr>
  <!-- Engine -->
  <tr>
    <td rowspan="1">Engines</td>
    <td colspan="2">Engines collection</td>
  </tr>
  <!-- Spoiler -->
  <tr>
    <td rowspan="1">Spoilers</td>
    <td colspan="2">Spoilers collection</td>
  </tr>
  <!-- Tires -->
  <tr>
    <td rowspan="1">Tires</td>
    <td colspan="2">Tires collection</td>
  </tr>
</table>

If you need helper C++ functions, the following are implemented in lua:

<table>
  <tr>
    <th>Function</th>
    <th>Description</th>
  </tr>
  <!-- Generic -->
  <tr>
    <td>print(string)</td>
    <td>print given string to terminal at current cursor position</td>
  </tr>
  <tr>
    <td>alert(string)</td>
    <td>add an alert with given string to current menu</td>
  </tr>
  <tr>
    <td>tostring(int)</td>
    <td>converts given integer and returns it in string form</td>
  </tr>
  <tr>
    <td>getCursor()</td>
    <td>returns integer position of cursor (Only hovereable items count)</td>
  </tr>
  <tr>
    <td>getInputData(id)</td>
    <td>returns string contained in input of given string Id (id)</td>
  </tr>
  <tr>
    <td>setInputData(id, value)</td>
    <td>sets string data (value) in input of given string Id (id)</td>
  </tr>
  <tr>
    <td>getSelectValue(id)</td>
    <td>returns string data (value) of selected option in select of given string Id (id)</td>
  </tr>
  <tr>
    <td>setSelectValue(id, value)</td>
    <td>sets option data (value) to select inside select of given string Id (id)</td>
  </tr>
  <tr>
    <td>addMenuItem(pos, xml)</td>
    <td>add Item in menu at position (pos) with XML Data (xml)</td>
  </tr>
  <tr>
    <td>selectCarMenu()</td>
    <td>go to a menu that allow player to select a car, sets environment variable "Box" to int selection index</td>
  </tr>
  <tr>
    <td>selectTrackMenu()</td>
    <td>go to a menu that allow player to select a Track, sets environment variable "Track" to int selection index</td>
  </tr>
</table>