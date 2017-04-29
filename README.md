# Qnote
#### Simple cross-platform (I believe) text editor based on QT framework
# It support
1. Syntax highlighting for C/C++, Java and C# using user-defined dictionaries (C,C++.xml, Java.xml, C#.xml).
    
    Example:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<highlighting>
    <controlflow>
      <item>break</item>
      <item>case</item>
      <item>continue</item>
      <item>default</item>
      <item>do</item>
      <item>else</item>
      <item>for</item>
      <item>goto</item>
      <item>if</item>
      <item>return</item>
      <item>switch</item>
      <item>while</item>
      <item>using</item>
      <item>public</item>
      <item>private</item>
      <item>signals</item>
      <item>slots</item>
      <item>new</item>
      <item>delete</item>
    </controlflow>
    <keywords>
      <item>enum</item>
      <item>extern</item>
      <item>inline</item>
      <item>sizeof</item>
      <item>struct</item>
      <item>typedef</item>
      <item>union</item>
      <item>class</item>
      <item>friend</item>
    </keywords>
    <types>
      <item>auto</item>
      <item>char</item>
      <item>const</item>
      <item>double</item>
      <item>float</item>
      <item>int</item>
      <item>long</item>
      <item>register</item>
      <item>restrict</item>
      <item>short</item>
      <item>signed</item>
      <item>static</item>
      <item>unsigned</item>
      <item>void</item>
      <item>volatile</item>
      <item>int8_t</item>
      <item>int16_t</item>
      <item>int32_t</item>
      <item>int64_t</item>
      <item>uint8_t</item>
      <item>uint16_t</item>
      <item>uint32_t</item>
      <item>uint64_t</item>
      <item>int_least8_t</item>
      <item>int_least16_t</item>
      <item>int_least32_t</item>
      <item>int_least64_t</item>
      <item>uint_least8_t</item>
      <item>uint_least16_t</item>
      <item>uint_least32_t</item>
      <item>uint_least64_t</item>
      <item>int_fast8_t</item>
      <item>int_fast16_t</item>
      <item>int_fast32_t</item>
      <item>int_fast64_t</item>
      <item>uint_fast8_t</item>
      <item>uint_fast16_t</item>
      <item>uint_fast32_t</item>
      <item>uint_fast64_t</item>
      <item>size_t</item>
      <item>ssize_t</item>
      <item>wchar_t</item>
      <item>intptr_t</item>
      <item>uintptr_t</item>
      <item>intmax_t</item>
      <item>uintmax_t</item>
      <item>ptrdiff_t</item>
      <item>sig_atomic_t</item>
      <item>wint_t</item>
      <item>_Imaginary</item>
      <item>_Complex</item>
      <item>_Bool</item>
    </types>
    <preprocessor>
      <item>define</item>
      <item>import</item>
      <item>undef</item>
      <item>elif</item>
      <item>if</item>
      <item>include</item>
      <item>using</item>
      <item>else</item>
      <item>ifdef</item>
      <item>line</item>
      <item>endif</item>
      <item>ifndef</item>
      <item>pragma</item>
      <item>error</item>
    </preprocessor>
  </highlighting>
  ```

  These dictionary xml's should be in the same dir as binary/exe file.

  2. Customization of text editor.

    Settings also can be changed via file `settings.xml`


```xml
<?xml version="1.0" encoding="UTF-8"?>
<settings>
    <textfield>
        <font>Kristen ITC</font>
        <font_size>8</font_size>
        <line_wrap_mode>1</line_wrap_mode>
        <line_numeration>1</line_numeration>
    </textfield>
    <highlighting>
        <language>C,C++</language>
        <colors>
            <background_color>#666666</background_color>
            <controlflow_color>#aaffff</controlflow_color>
            <keywords_color>#00ff00</keywords_color>
            <types_color>#55aaff</types_color>
            <preprocessor_color>#bababa</preprocessor_color>
            <normal_text_color>#ffffff</normal_text_color>
            <comments_color>#ffaaff</comments_color>
            <functions_color>#ffff7f</functions_color>
            <search_background_color>#ffff7f</search_background_color>
            <search_text_color>#000000</search_text_color>
            <quotes_color>#aaff7f</quotes_color>
            <classes_color>#ff55ff</classes_color>
        </colors>
    </highlighting>
</settings>
```
  3. Git-gui and gitk support (you need to install and configure them before using).


  # TODO

  * Make possible to move document to new window