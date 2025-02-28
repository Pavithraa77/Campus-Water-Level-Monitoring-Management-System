import React, { useEffect, useState } from 'react';
import { View, Text, ScrollView, FlatList, StyleSheet, ActivityIndicator } from 'react-native';
import Svg, { Rect, Text as SvgText } from 'react-native-svg';

// ... Keep the same imports and constants from original code ...

const InfluxDataScreen = () => {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [currentLevel, setCurrentLevel] = useState(0);

  useEffect(() => {
    const getData = async () => {
      const influxData = await fetchInfluxData();
      if (influxData) {
        const parsedData = parseCSV(influxData);
        setData(parsedData);
        if (parsedData.length > 0) {
          const latest = parseFloat(parsedData[parsedData.length - 1].litres);
          setCurrentLevel(latest);
        }
      }
      setLoading(false);
    };

    getData();
  }, []);

  const WaterTank = () => {
    const tankWidth = 200;
    const tankHeight = 300;
    const fillHeight = Math.min((currentLevel / 3.5) * tankHeight, tankHeight);

    return (
      <View style={styles.tankContainer}>
        <Svg height={tankHeight + 40} width={tankWidth}>
          {/* Tank Outline */}
          <Rect
            x="0"
            y="0"
            width={tankWidth}
            height={tankHeight}
            stroke="#00ff00"
            strokeWidth="4"
            fill="none"
            rx="10"
          />
          
          {/* Water Fill */}
          <Rect
            x="4"
            y={tankHeight - fillHeight + 4}
            width={tankWidth - 8}
            height={fillHeight - 8}
            fill="#00ff00"
            opacity={0.4}
            rx="6"
          />
          
          {/* Capacity Text */}
          <SvgText
            x={tankWidth / 2}
            y={tankHeight + 30}
            fill="#00ff00"
            fontSize="16"
            fontWeight="bold"
            textAnchor="middle"
          >
            {currentLevel.toFixed(2)} / 3.5 L
          </SvgText>
        </Svg>
      </View>
    );
  };

  return (
    <View style={styles.container}>
      <Text style={styles.heading}>Water Level Monitoring</Text>

      {loading ? (
        <ActivityIndicator size="large" color="#00ff00" />
      ) : (
        <>
          <WaterTank />
          
          <Text style={styles.subHeading}>Historical Data</Text>
          {data.length > 0 ? (
            <ScrollView horizontal>
              <View>
                <View style={styles.headerRow}>
                  <Text style={styles.headerText}>Timestamp</Text>
                  <Text style={styles.headerText}>Litres</Text>
                </View>

                <FlatList
                  data={data.reverse()} // Show latest first
                  keyExtractor={(item, index) => index.toString()}
                  renderItem={({ item }) => (
                    <View style={styles.row}>
                      <Text style={styles.cellText}>{item.timestamp}</Text>
                      <Text style={styles.cellText}>{parseFloat(item.litres).toFixed(2)}</Text>
                    </View>
                  )}
                />
              </View>
            </ScrollView>
          ) : (
            <Text style={styles.errorText}>No data available</Text>
          )}
        </>
      )}
    </View>
  );
};

const styles = StyleSheet.create({
  container: { flex: 1, padding: 20, backgroundColor: '#121212' },
  heading: { 
    fontSize: 24, 
    fontWeight: 'bold', 
    color: '#00ff00', 
    textAlign: 'center', 
    marginBottom: 20,
    textTransform: 'uppercase',
    letterSpacing: 1.5,
  },
  subHeading: {
    fontSize: 18,
    color: '#00ff00',
    marginVertical: 15,
    paddingLeft: 10,
    borderLeftWidth: 3,
    borderLeftColor: '#00ff00',
  },
  tankContainer: {
    alignItems: 'center',
    marginVertical: 20,
  },
  // ... Keep other styles from original code ...
});

export default InfluxDataScreen;