# JUnit

JUnit是一个开源的Java语言的单元测试框架，专门针对Java设计，使用最广泛



# 单元测试

当我们已经编写了一个`Factorial.java`文件后，我们想对其进行测试，需要编写一个对应的`FactorialTest.java`文件，以`Test`为后缀是一个惯例，并分别将其放入`src`和`test`目录中

```java
public class FactorialTest {
    // 在所有Test前执行（只能用于静态方法）
    @BeforeAll
    public static void initDatabase() {
        db = createDb(...);
    }
    // 在每个Test前执行
    @BeforeEach
    public void setUp() {
        this.calculator = new Calculator();
    }
    // 单元测试方法
    @Test
    void testFact() {
        assertEquals(1, Factorial.fact(1)); // 期望相等
        assertEquals(0.1, Math.abs(1 - 9 / 10.0), 0.0000001); // 浮点数比较
        
        assertTrue(Factorial.fact(2)); // 期待结果为true
        assertFalse(Factorial.fact(3)); // 期待结果为false
        assertNotNull(Factorial.fact(10));  // 期待结果为非null
        assertArrayEquals(Factorial.fact(20)); // 期待结果为数组并与期望数组每个元素的值均相等
        
        assertThrows(IllegalArgumentException.class, () -> { // 异常测试
        	Factorial.fact(-1);
   		});
    }
	// 在每个Test后执行
    @AfterEach
    public void tearDown() {
        this.calculator = null;
    }
    // 在所有Test后执行（只能用于静态方法）
    @AfterAll
    public static void dropDatabase() {
        ...
    }
}
```



# 条件测试

```java
@Disabled // 排除某个Test方法
@EnabledOnOs(OS.WINDOWS) // 指定操作系统
@DisabledOnOs(OS.WINDOWS)
@DisabledOnJre(JRE.JAVA_8) // 只能在Java 9或更高版本执行的测试
@EnabledIfSystemProperty(named = "os.arch", matches = ".*64.*") // 只能在64位操作系统上执行的测试
@EnabledIfEnvironmentVariable(named = "DEBUG", matches = "true") // 需要传入环境变量DEBUG=true才能执行的测试
```



# 参数化测试

如果待测试的输入和输出是一组数据： 可以把测试数据组织起来 用不同的测试数据调用相同的测试方法

参数化测试和普通测试稍微不同的地方在于，一个测试方法需要接收至少一个参数，然后，传入一组参数反复运行。

JUnit提供了一个`@ParameterizedTest`注解，用来进行参数化测试。



```java
// 对Math.abs()进行测试，用一组正数进行测试
@ParameterizedTest
@ValueSource(ints = { 0, 1, 5, 100 })
void testAbs(int x) {
    assertEquals(x, Math.abs(x));
}

// @MethodSource，名的静态方法testCapitalize()返回了一组测试参数
@ParameterizedTest
@MethodSource
void testCapitalize(String input, String result) {
    assertEquals(result, StringUtils.capitalize(input));
}

static List<Arguments> testCapitalize() {
    return List.of( // arguments:
            Arguments.arguments("abc", "Abc"), //
            Arguments.arguments("APPLE", "Apple"), //
            Arguments.arguments("gooD", "Good"));
}

// @CsvSource，它的每一个字符串表示一行，一行包含的若干参数用,分隔
@ParameterizedTest
@CsvSource({ "abc, Abc", "APPLE, Apple", "gooD, Good" })
void testCapitalize(String input, String result) {
    assertEquals(result, StringUtils.capitalize(input));
}

// 读取CSV文件测试
@ParameterizedTest
@CsvFileSource(resources = { "/test-capitalize.csv" })
void testCapitalizeUsingCsvFile(String input, String result) {
    assertEquals(result, StringUtils.capitalize(input));
}
```





























