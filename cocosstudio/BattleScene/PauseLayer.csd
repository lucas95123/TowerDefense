<GameFile>
  <PropertyGroup Name="PauseLayer" Type="Layer" ID="ddeb9361-ed42-48a5-9407-0c630edb26be" Version="2.3.3.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" Tag="10" ctype="GameLayerObjectData">
        <Size X="960.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="Panel_1" ActionTag="-1088263052" Tag="32" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="179.0400" RightMargin="180.9600" TopMargin="141.0240" BottomMargin="138.9760" TouchEnable="True" BackColorAlpha="204" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="600.0000" Y="360.0000" />
            <Children>
              <AbstractNodeData Name="pause_3" ActionTag="1277124987" Tag="51" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="52.5000" RightMargin="52.5000" TopMargin="27.5000" BottomMargin="207.5000" ctype="SpriteObjectData">
                <Size X="495.0000" Y="125.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="300.0000" Y="270.0000" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.7500" />
                <PreSize X="0.8250" Y="0.3472" />
                <FileData Type="Normal" Path="BattleScene/pauseMenu.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Resume" ActionTag="-1454899944" Tag="41" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-279.5000" RightMargin="20.5000" TopMargin="-177.5000" BottomMargin="-321.5000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="829" Scale9Height="837" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="859.0000" Y="859.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="150.0000" Y="108.0000" />
                <Scale ScaleX="0.1000" ScaleY="0.1000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2500" Y="0.3000" />
                <PreSize X="1.4317" Y="2.3861" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="BattleScene/Start.png" Plist="" />
                <NormalFileData Type="Normal" Path="BattleScene/StartTrans.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Back" ActionTag="887590038" Tag="42" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-129.5000" RightMargin="-129.5000" TopMargin="-177.5000" BottomMargin="-321.5000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="829" Scale9Height="837" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="859.0000" Y="859.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="300.0000" Y="108.0000" />
                <Scale ScaleX="0.1000" ScaleY="0.1000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3000" />
                <PreSize X="1.4317" Y="2.3861" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="BattleScene/return.png" Plist="" />
                <NormalFileData Type="Normal" Path="BattleScene/returnTrans.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="CheckBox_Sound" ActionTag="1195793771" Tag="173" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="20.5000" RightMargin="-279.5000" TopMargin="-177.5000" BottomMargin="-321.5000" TouchEnable="True" ctype="CheckBoxObjectData">
                <Size X="859.0000" Y="859.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="450.0000" Y="108.0000" />
                <Scale ScaleX="0.1000" ScaleY="0.1000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7500" Y="0.3000" />
                <PreSize X="1.4317" Y="2.3861" />
                <NormalBackFileData Type="Normal" Path="BattleScene/SoundOnTrans.png" Plist="" />
                <PressedBackFileData Type="Normal" Path="BattleScene/SoundOn.png" Plist="" />
                <DisableBackFileData Type="Default" Path="Default/CheckBox_Disable.png" Plist="" />
                <NodeNormalFileData Type="Normal" Path="BattleScene/cross.png" Plist="" />
                <NodeDisableFileData Type="Normal" Path="BattleScene/cross.png" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="479.0400" Y="318.9760" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4990" Y="0.4984" />
            <PreSize X="0.6250" Y="0.5625" />
            <SingleColor A="255" R="26" G="26" B="26" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>